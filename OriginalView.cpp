//
// originalview.cpp
//
// The code maintaining the original view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "originalview.h"
#include "LineBrush.h"

#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#endif

OriginalView::OriginalView(int			x, 
						   int			y, 
						   int			w, 
						   int			h, 
						   const char*	l)
							: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}

void OriginalView::draw()
{
	if(!valid())
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		// Tell openGL to read from the front buffer when capturing
		// out paint strokes 
		glReadBuffer( GL_FRONT );
		ortho();

	}

	glClear( GL_COLOR_BUFFER_BIT );

	if ( m_pDoc->m_ucBitmap ) 
	{
		// note that both OpenGL pixel storage and the Windows BMP format
		// store pixels left-to-right, BOTTOM-to-TOP!!  thus all the fiddling
		// around with startrow.

		m_nWindowWidth=w();
		m_nWindowHeight=h();

		// we are not using a scrollable window, so ignore it
		Point scrollpos;	// = GetScrollPosition();
		scrollpos.x=scrollpos.y=0;

		m_nDrawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
		m_nDrawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

		int	startrow	= m_pDoc->m_nHeight - (scrollpos.y + m_nDrawHeight);
		if ( startrow < 0 ) 
			startrow = 0;

		m_nStartRow = startrow;
		m_nEndRow = startrow + m_nDrawHeight;
		m_nStartCol = scrollpos.x;
		m_nEndCol = m_nStartCol + m_nDrawWidth;

		m_pOrigBitstart = m_pDoc->m_ucBitmap + 3 * ((m_pDoc->m_nWidth * startrow) + scrollpos.x);

		// just copy image to GLwindow conceptually
		glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight);
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
		glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nWidth );
		glDrawBuffer( GL_BACK );
		glDrawPixels(m_nDrawWidth, m_nDrawHeight, GL_RGB, GL_UNSIGNED_BYTE, m_pOrigBitstart);

		((ImpBrush*)m_pDoc->m_pCurrentBrush)->drawCursor(cursorPos);
	}

	glFlush();
}

void OriginalView::refresh()
{
	redraw();
}

void OriginalView::drawCursor(Point source) {
	cursorPos = Point(source.x + m_nStartCol, m_nWindowHeight - (m_nEndRow - source.y));
	refresh();
}
/*
int OriginalView::handle(int event) {
	switch (event)
	{
	case FL_ENTER:
		redraw();
		break;
	case FL_MOVE:
		redraw();
		break;
	default:
		return 0;
		break;

	}
	return 1;
}
*/
void OriginalView::resizeWindow(int	width, 
								int	height)
{
	resize(x(), y(), width, height);
}

void OriginalView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);

	glReadPixels(0,
		m_nWindowHeight - m_nDrawHeight,
		m_nDrawWidth,
		m_nDrawHeight,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		m_pOrigBitstart);
}


void OriginalView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2i(0, m_nWindowHeight - m_nDrawHeight);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);
	glDrawPixels(m_nDrawWidth,
		m_nDrawHeight,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		m_pOrigBitstart);

	//	glDrawBuffer(GL_FRONT);
}