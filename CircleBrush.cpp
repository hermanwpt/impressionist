//
// CircleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include <math.h>

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {
	for (int i = 0; i < NUM_SEGMENTS; ++i) {
		double angle = (double)(2 * M_PI) * ((double)i / (double)NUM_SEGMENTS);

		sinValues[i] = sin(angle);
		cosValues[i] = cos(angle);
	}
}

void CircleBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glPointSize(1);	// Point size is irrelevant because "brush size" determines radius

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}
	
	double radius = pDoc->getSize() / 2;
	
	glBegin(GL_POLYGON);
	SetColor(source);
	
	for (int i = 0; i < NUM_SEGMENTS; ++i) {
		
		double xOffset = radius * cosValues[i];
		double yOffset = radius * sinValues[i];

		glVertex2d(source.x + xOffset, source.y + yOffset);
	}
	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}