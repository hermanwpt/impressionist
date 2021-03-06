//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//


#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"
#include "LineBrush.h"
#include <math.h>
#include <vector>
#include <algorithm>

#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;

extern float frand();

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nAuto = false;
	m_nDissolve = false;
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}


void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA

	// Enable border clipping
	// glEnable(GL_SCISSOR_TEST);

	// Enable edge clipping (using stencil buffer)
	glEnable(GL_STENCIL_TEST);
	glClearStencil(0);					// 0 means "do not display"
	glStencilMask(0xFF);
	glStencilFunc(GL_EQUAL, 1, 0xFF);	// 1 means "display"

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);	// Always draw to the stencil buffer

	glClear(GL_STENCIL_BUFFER_BIT);						// Clear the stencil buffer, effectively making them all 0s

	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);				// Force OpenGL to not draw to stencil buffer at all
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	
	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if(!valid())
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		glClear( GL_COLOR_BUFFER_BIT );
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;

	// Draw border for clipping
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);	// Always draw to the stencil buffer

	glBegin(GL_POLYGON);
		glVertex2f(0, m_nWindowHeight - m_nDrawHeight);
		glVertex2f(m_nDrawWidth, m_nWindowHeight - m_nDrawHeight);
		glVertex2f(m_nDrawWidth, m_nWindowHeight);
		glVertex2f(0, m_nWindowHeight);
	glEnd();

	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);				// Force OpenGL to not draw to stencil buffer at all
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);


	// Handles Autopaint event
	if (m_pDoc->m_ucPainting && (m_nAuto || m_nDissolve)) {
		int spacing = m_pDoc->getSpacing();
		int origSize = m_pDoc->m_pUI->getSize();
		bool randSize = m_pDoc->getSizeRandom();
		std::vector<int> xCoors, yCoors;
		for (int i = 0; i < m_nDrawWidth; i += spacing) {
			xCoors.push_back(i);
		}
		for (int i = 0; i < m_nDrawHeight; i += spacing) {
			yCoors.push_back(i);
		}
		std::random_shuffle(xCoors.begin(), xCoors.end());
		std::random_shuffle(yCoors.begin(), yCoors.end());

		for (int i = 0; i < xCoors.size(); ++i) {
			for (int j = 0; j < yCoors.size(); ++j) {
				if (randSize) {
					m_pDoc->m_pUI->setSize(origSize * (frand() + 0.5));
				}
				m_pDoc->m_pCurrentBrush->BrushMove(Point(xCoors[i] + m_nStartCol, m_nEndRow - yCoors[j]), Point(xCoors[i], m_nWindowHeight - yCoors[j]));
			}
		}

		m_pDoc->m_pUI->setSize(origSize);
		m_nAuto = false;
		m_nDissolve = false;
		SaveCurrentContent();
		RestoreContent();
	}

	// Handles when no painting is occuring
	if ( m_pDoc->m_ucPainting && !isAnEvent) 
	{
		RestoreContent();

	}

	// Handles normal painting events
	if ( m_pDoc->m_ucPainting && isAnEvent) 
	{

		// Clear it after processing.
		isAnEvent	= 0;	

		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );
		
		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			m_pDoc->saveLastPaint();
			m_pDoc->m_pCurrentBrush->BrushBegin( source, target );
			break;
		case LEFT_MOUSE_DRAG:
			m_pDoc->m_pCurrentBrush->BrushMove( source, target );
			break;
		case LEFT_MOUSE_UP:
			m_pDoc->m_pCurrentBrush->BrushEnd( source, target );

			SaveCurrentContent();
			RestoreContent();
			break;

		// Only valid when using LINE brush and using slider/right-click to control the direction
		case RIGHT_MOUSE_DOWN:
			// Save current coordinates to calculate new size/angle later
			if ((m_pDoc->getBrushType() == BRUSH_LINES) || (m_pDoc->getBrushType() == BRUSH_SCATTERED_LINES)) {
				m_lStartX = source.x;
				m_lStartY = source.y;
			}
			break;
		case RIGHT_MOUSE_DRAG:
			RestoreContent();
			// Draw "cursor"
			
			((LineBrush*)m_pDoc->m_pCurrentBrush)->drawCursor(Point(m_lStartX, m_lStartY), source);

			break;
		case RIGHT_MOUSE_UP:
			// Calculate new size/angles
			if ((m_pDoc->getBrushType() == BRUSH_LINES) || (m_pDoc->getBrushType() == BRUSH_SCATTERED_LINES)) {
				m_lEndX = source.x;
				m_lEndY = source.y;

				double temp;
				if (m_lEndX - m_lStartX != 0) {
					temp = atan2((m_lEndY - m_lStartY), (m_lEndX - m_lStartX));	// Use atan2 instead for real-time operations
				}
				else {
					temp = M_PI / 2;
				}

				int size = m_pDoc->getSize();
				int angle;

				size = sqrt((m_lEndY - m_lStartY) * (m_lEndY - m_lStartY) + (m_lEndX - m_lStartX) * (m_lEndX - m_lStartX));

				if (temp < 0) {
					angle = ((2 * M_PI + temp) / (2 * M_PI) * 360);
				} else {
					angle = (temp / (2 * M_PI) * 360);
				}

				m_pDoc->m_pUI->setSize(size);
				m_pDoc->m_pUI->setAngle(angle);
			}

			RestoreContent();
			break;

		default:
			printf("Unknown event!!\n");		
			break;
		}
	}

	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA

}


int PaintView::handle(int event)
{
	switch(event)
	{
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		redraw();

		// Invoke OriginalView to draw cursor
		m_pDoc->m_pUI->m_origView->drawCursor(Point(coord.x + m_nStartCol, m_nEndRow - coord.y));
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();

		// Invoke OriginalView to draw cursor
		m_pDoc->m_pUI->m_origView->drawCursor(Point(coord.x + m_nStartCol, m_nEndRow - coord.y));
		break;
	default:
		return 0;
		break;

	}



	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}


void PaintView::RestoreContent()
{	
	// Draw image
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

//	glDrawBuffer(GL_FRONT);
}


void PaintView::setAutoPaint(bool flag)
{
	m_nAuto = flag;
}

void PaintView::setDissolve(bool flag)
{
	m_nDissolve = flag;
}

bool PaintView::getDissolve()
{
	return m_nDissolve;
}
