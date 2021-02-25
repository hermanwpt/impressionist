//
// ScatteredTriangleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredTriangleBrush.h"

extern float frand();

ScatteredTriangleBrush::ScatteredTriangleBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {
}

void ScatteredTriangleBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glPointSize(1);	// Point size is irrelevant because "brush size" determines radius

	BrushMove(source, target);
}

void ScatteredTriangleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredTriangleBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	double halfSize = (double)size / 2;
	for (int i = 0; i < NUM_TRIANGLES; ++i) {
		double xOffset = (double)frand() * (double)size - halfSize;
		double yOffset = (double)frand() * (double)size - halfSize;

		c_pBrushes[BRUSH_TRIANGLES]->BrushMove(Point(target.x + xOffset, target.y + yOffset), Point(target.x + xOffset, target.y + yOffset));
	}
}

void ScatteredTriangleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

