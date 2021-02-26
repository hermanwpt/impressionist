//
// TriangleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "TriangleBrush.h"
#include <queue>
#include <math.h>

extern float frand();

TriangleBrush::TriangleBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {
	for (int i = 0; i < NUM_SEGMENTS; ++i) {
		double angle = (double)(2 * M_PI) * ((double)i / (double)NUM_SEGMENTS);

		sinValues[i] = sin(angle);
		cosValues[i] = cos(angle);
	}
	prevloc.x = 0;
	prevloc.y = 0;
}

void TriangleBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void TriangleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("TriangleBrush::BrushMove  document is NULL\n");
		return;
	}

	int x = source.x;
	int y = source.y;
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



	// Then process image drawing
	double radius = pDoc->getSize() / 2;
	int angle;

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
		angle = (pDoc->getAngle() % 360);
		break;
	case STROKE_GRADIENT:
		// Prevent coordinates from going out of bound
		x = target.x;
		y = target.y;
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

		if (gradient[x][y].a != 0) {
			temp = atan2((gradient[x][y]).b, (gradient[x][y]).a); // Use atan2 instead for real-time operations
		}
		else {
			temp = M_PI / 2;
		}

		if (temp < 0) {
			angle = (int)(((2 * M_PI + temp) / (2 * M_PI) * 360) - 90) % 360;
		}
		else {
			angle = (int)((temp / (2 * M_PI) * 360) + 90) % 360;
		}
		break;
	case STROKE_BRUSH_DIRECTION:
		if (prevloc.x - source.x != 0) {
			temp = atan2((source.y - prevloc.y), (source.x - prevloc.x)); // Use atan2 instead for real-time operations
		}
		else {
			if (prevloc.y > source.y) {
				temp = 3 * M_PI / 2;
			}
			else {
				temp = M_PI / 2;
			}
		}
		if (temp < 0) {
			angle = ((2 * M_PI + temp) / (2 * M_PI) * 360);
		}
		else {
			angle = (temp / (2 * M_PI) * 360);
		}
		break;
	default:
		break;
	}

	prevloc.x = source.x;
	prevloc.y = source.y;

	size = pDoc->getSize() / 2;
	
	glBegin(GL_POLYGON);
	SetColor(source);
		glVertex2f(target.x + size * cosValues[angle], target.y + size * sinValues[angle]);
		glVertex2f(target.x + size * cosValues[(angle + 120) % 360], target.y + size * sinValues[(angle + 120) % 360]);
		glVertex2f(target.x + size * cosValues[(angle + 240) % 360], target.y + size * sinValues[(angle + 240) % 360]);
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

void TriangleBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}