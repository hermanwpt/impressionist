//
// ScatteredCrescentBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredCrescentBrush.h"

extern float frand();

ScatteredCrescentBrush::ScatteredCrescentBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {
}

void ScatteredCrescentBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glPointSize(1);	// Point size is irrelevant because "brush size" determines radius

	BrushMove(source, target);
}

void ScatteredCrescentBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredCrescentBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	double halfSize = (double)size / 2;
	for (int i = 0; i < NUM_CRESCENTS; ++i) {
		double xOffset = (double)frand() * (double)size - halfSize;
		double yOffset = (double)frand() * (double)size - halfSize;

		c_pBrushes[BRUSH_CRESCENTS]->BrushMove(Point(target.x + xOffset, target.y + yOffset), Point(target.x + xOffset, target.y + yOffset));
	}
}

void ScatteredCrescentBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

