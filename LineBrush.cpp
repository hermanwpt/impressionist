//
// LineBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {
	for (int i = 0; i < NUM_SEGMENTS; ++i) {
		double angle = (double)(2 * M_PI) * ((double)i / (double)NUM_SEGMENTS);

		sinValues[i] = sin(angle);
		cosValues[i] = cos(angle);
	}

	prevloc.x = 0;
	prevloc.y = 0;
}

void LineBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int width = pDoc->getWidth();

	glLineWidth((float)width);

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_LINES);
	SetColor(source);

	int angle, x, y;
	double temp;
	intPair** gradient = pDoc->g_ucOrig;
	switch (pDoc->getStrokeDirectionType()) {
	case STROKE_SLIDER:
		angle = pDoc->getAngle();
		break;
	case STROKE_GRADIENT:
		// Prevent coordinates from going out of bound
		x = source.x;
		y = source.y;
		if (x < 0) {
			x = 0;
		} else if (x > pDoc->m_nWidth - 1) {
			x = pDoc->m_nWidth - 1;
		}

		if (y < 0) {
			y = 0;
		} else if (y > pDoc->m_nHeight - 1) {
			y = pDoc->m_nHeight - 1;
		}

		if (gradient[x][y].a != 0) {
			temp = atan2((gradient[x][y]).b, (gradient[x][y]).a); // Use atan2 instead for real-time operations
		} else {
			temp = M_PI / 2;
		}

		if (temp < 0) {
			angle = ((2 * M_PI + temp) / (2 * M_PI) * 360) - 90;
		} else {
			angle = (temp / (2 * M_PI) * 360) + 90;
		}
		break;
	case STROKE_BRUSH_DIRECTION:
		printf("Source: (%d, %d)\t\tPrevloc: (%d, %d)\n", source.x, source.y, prevloc.x, prevloc.y);
		if (prevloc.x - source.x != 0) {
			temp = atan2((source.y - prevloc.y), (source.x - prevloc.x)); // Use atan2 instead for real-time operations
		} else {
			temp = M_PI / 2;
		}
		if (temp < 0) {
			angle = ((2 * M_PI + temp) / (2 * M_PI) * 360);
		} else {
			angle = (temp / (2 * M_PI) * 360);
		}
		break;
	default:
		break;
	}

	prevloc.x = source.x;
	prevloc.y = source.y;
	
	int length = pDoc->getSize();
	double halfLength = (double)length / 2;
	double xOffset = halfLength * cosValues[angle];
	double yOffset = halfLength * sinValues[angle];

	glVertex2d(target.x + xOffset, target.y + yOffset);
	glVertex2d(target.x - xOffset, target.y - yOffset);

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

void LineBrush::drawCursor(const Point source, const Point target) {
	glBegin(GL_LINES);
	glColor4f(1.00, 0.00, 0.00, 1.00);
		glVertex2d(source.x, source.y);
		glVertex2d(target.x, target.y);
	glEnd();
}
