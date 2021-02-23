//
// LineBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"
#include <queue>

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

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	int angle, x, y;
	double temp;
	intPair** gradient;
	if (pDoc->getAnotherGradient()) {
		gradient = pDoc->g_ucAnother;
	}
	else {
		gradient = pDoc->g_ucOrig;
	}
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
	
	x = source.x;
	y = source.y;
	if (x < 0) {
		x = 0;
	}
	else if (x > pDoc->m_nWidth - 1) {
		x = pDoc->m_nWidth - 1;
	}

	if (y < 0) {
		y = 0;
	}
	else if (y > pDoc->m_nHeight - 1) {
		y = pDoc->m_nHeight - 1;
	}

	int size = pDoc->getSize();

	if (pDoc->getClip()) {
		int halfSize = (double)size / 2;

		int width = pDoc->m_nPaintWidth;
		int height = pDoc->m_nPaintHeight;
		int xLowerBound = max(x - halfSize, 0);
		int xUpperBound = min(x + halfSize, width - 1);
		int yLowerBound = max(y - halfSize, 0);
		int yUpperBound = min(y + halfSize, height - 1);

		int step = CLIPPING_SAMPLE_SIZE;	// Change this for faster/slower approximation

		BFSVertex** map = pDoc->e_ucEdge;

		// Process clipping first
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);	// Always draw to the stencil buffer

		glClear(GL_STENCIL_BUFFER_BIT);	// Clear the stencil buffer, effectively making them all 0s

		// Reset "checked" flag to false for all BFS vertices
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				pDoc->e_ucEdge[i][j].checked = false;
			}
		}
		BFSVertex* sourceVertex = &(map[x][y]);


		glPointSize(step);

		glBegin(GL_POINTS);
		std::queue<BFSVertex*> bfsQueue;

		bfsQueue.push(sourceVertex);
		while (!bfsQueue.empty()) {
			BFSVertex* cur = bfsQueue.front();
			if (cur->data == sourceVertex->data) {
				glVertex2f(cur->x, cur->y);
				cur->checked = true;
				bfsQueue.pop();
			}
			else {
				cur->checked = true;
				bfsQueue.pop();
				continue;
			}

			BFSVertex* adj = &map[max(cur->x - step, xLowerBound)][cur->y];
			if (!adj->checked) {
				bfsQueue.push(adj);
				adj->checked = true;
			}

			adj = &map[min(cur->x + step, xUpperBound)][cur->y];
			if (!adj->checked) {
				bfsQueue.push(adj);
				adj->checked = true;
			}

			adj = &map[cur->x][max(cur->y - step, yLowerBound)];
			if (!adj->checked) {
				bfsQueue.push(adj);
				adj->checked = true;
			}

			adj = &map[cur->x][min(cur->y + step, yUpperBound)];
			if (!adj->checked) {
				bfsQueue.push(adj);
				adj->checked = true;
			}
		}

		glEnd();

		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);				// Force OpenGL to not draw to stencil buffer at all
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}


	int width = pDoc->getWidth();


	glLineWidth((float)width);

	int length = pDoc->getSize();
	double halfLength = (double)length / 2;
	double xOffset = halfLength * cosValues[angle];
	double yOffset = halfLength * sinValues[angle];
	glBegin(GL_LINES);
	SetColor(source);

		glVertex2d(target.x + xOffset, target.y + yOffset);
		glVertex2d(target.x - xOffset, target.y - yOffset);

	glEnd();

	// Clear previously applied clipping
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);	// Always draw to the stencil buffer

	glClear(GL_STENCIL_BUFFER_BIT);						// Clear the stencil buffer, effectively making them all 0s
	glBegin(GL_POLYGON);
	glVertex2f(0, pDoc->m_nHeight - pDoc->m_nPaintHeight);
	glVertex2f(pDoc->m_nPaintWidth, pDoc->m_nHeight - pDoc->m_nPaintHeight);
	glVertex2f(pDoc->m_nPaintWidth, pDoc->m_nHeight);
	glVertex2f(0, pDoc->m_nHeight);
	glEnd();

	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);				// Force OpenGL to not draw to stencil buffer at all
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
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

