//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{

}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor(const Point source) {
	ImpressionistDoc* pDoc = GetDocument();


	GLubyte color[3];
	double alpha = pDoc->getAlpha();
	double blendR = pDoc->getColorR();
	double blendG = pDoc->getColorG();
	double blendB = pDoc->getColorB();

	if (pDoc->m_pUI->m_paintView->getDissolve()) {
		int x = source.x;
		int y = source.y;

		if (x < 0) x = 0;
		else if (x >= pDoc->m_nWidth) x = pDoc->m_nWidth - 1;

		if (y < 0) y = 0;
		else if (y >= pDoc->m_nHeight) y = pDoc->m_nHeight - 1;

		color[0] = (GLubyte)(pDoc->m_ucAnother[3 * (y * pDoc->m_nWidth + x)]);
		color[1] = (GLubyte)(pDoc->m_ucAnother[3 * (y * pDoc->m_nWidth + x) + 1]);
		color[2] = (GLubyte)(pDoc->m_ucAnother[3 * (y * pDoc->m_nWidth + x) + 2]);
	} else {
		memcpy(color, pDoc->GetOriginalPixel(source), 3);
	}

	glColor4f(
		(float)color[0] / 255.0f * blendR,
		(float)color[1] / 255.0f * blendG,
		(float)color[2] / 255.0f * blendB,
		(float)alpha
	);
}

void ImpBrush::drawCursor(const Point source) {
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor4f(1, 0, 0, 1);
		glVertex2d(source.x, source.y);
	glEnd();
}