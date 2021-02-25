#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CustomBrush.h"

extern float frand();

CustomBrush::CustomBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CustomBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	int width = pDoc->m_nWidth;
	int height = pDoc->m_nHeight;

	img = new unsigned char[width * height * 3];
	memcpy(img, pDoc->m_ucPainting, width * height * 3);

	glPointSize((float)size);

	BrushMove(source, target);
}

void CustomBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CustomBrush::BrushMove  document is NULL\n");
		return;
	}

	int width = pDoc->m_nPaintWidth;
	int height = pDoc->m_nPaintHeight;

	if (img == nullptr) {
		img = new unsigned char[width * height * 3];
		memcpy(img, pDoc->m_ucPainting, width * height * 3);
	}

	int x = source.x;
	int y = source.y;
	if (x < 0) {
		x = 0;
	}
	else if (x > width - 1) {
		x = width - 1;
	}
	if (y < 0) {
		y = 0;
	}
	else if (y > height - 1) {
		y = height - 1;
	}

	int size = pDoc->getSize();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int x = source.x + i - size / 2;
			int y = source.y + j - size / 2;
			if (x < 0 || x > width - 1 || y < 0 || y > height - 1) {
				continue;
			}
			applyFilter(x, y);
		}
	}
	dlg->m_paintView->RestoreContent();
}

void CustomBrush::BrushEnd(const Point source, const Point target)
{
	//delete[] img;
}

void CustomBrush::selectFilter(filterType type) {
	switch (type) {
	case SHARPENING:							// Wiki Sharpening Blur
		filter = {	{-1, -1, -1},
					{-1, 9, -1},
					{-1, -1, -1} };
		filterSize = 3;
		break;
	case BLUR:									// Wiki Gaussian Blur
		filter = {	{1, 2, 1},
					{2, 4, 2},
					{1, 2, 1} };
		for (int i = 0; i < 9; i++)
			filter[i / 3][i % 3] /= 16;
		filterSize = 3;
		break;
	default:
		filter = { {1} }; 
		filterSize = 1;
	}
}

void CustomBrush::applyFilter(int x, int y) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int width = pDoc->m_nPaintWidth;
	int height = pDoc->m_nPaintHeight;
	
	for (int rgb = 0; rgb < 3; rgb++) {
		int px = 0;
		for (int i = 0; i < filterSize; i++) {
			for (int j = 0; j < filterSize; j++) {
				int pixelX = x - filterSize / 2 + i;
				int pixelY = y - filterSize / 2 + j;
				if (pixelX < 0 || pixelX > width - 1 || pixelY < 0 || pixelY > height - 1) {
					continue;
				}
				px += filter[i][j] * img[(pixelY * width + pixelX) * 3 + rgb];
			}
		}
		pDoc->m_ucPainting[(y * width + x) * 3 + rgb] = min(255, max(0, px));
	}
}
