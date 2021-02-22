//
// CircleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include <queue>
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

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
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
	glPointSize(1);	// Point size is irrelevant because "brush size" determines radius
	double radius = pDoc->getSize() / 2;
	
	glBegin(GL_POLYGON);
	SetColor(source);
	
	for (int i = 0; i < NUM_SEGMENTS; ++i) {
		
		double xOffset = radius * cosValues[i];
		double yOffset = radius * sinValues[i];

		glVertex2d(target.x + xOffset, target.y + yOffset);
	}
	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}