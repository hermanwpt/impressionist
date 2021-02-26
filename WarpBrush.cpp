// 
// WarpBrush.cpp
// 
// This implementation has taken reference from 
// - https://www.cs.princeton.edu/courses/archive/fall00/cs426/lectures/warp/warp.pdf
// - http://www.connellybarnes.com/work/class/2016/intro_gfx/lectures/03-Image.pdf
// - https://github.com/cxcxcxcx/imgwarp-opencv
// The idea is newImg[source.x+displacement.x, source.y+displacement.y] = oldImg[source.x, source.y]
// We use Forward Mapping and Gaussian Filter Resampling.

#include "Impressionist.h"
#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "WarpBrush.h"
#include <iostream>

using namespace std;

extern float fraud();

inline double Pythagoras(double x, double y) {
	return sqrt(x * x + y * y);
}

WarpBrush::WarpBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {
}

void WarpBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();

	int size = pDoc->getSize();

	glPointSize((float)size);

	src = Point{ target.x, target.y };

	BrushMove(source, target);
}

void WarpBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CustomBrush::BrushMove  document is NULL\n");
		return;
	}

	int width = pDoc->m_nWidth;
	int height = pDoc->m_nHeight;

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

	// keep record of the oldImg
	unsigned char* img = new unsigned char[width * height * 3];
	memcpy(img, pDoc->m_ucPainting, width * height * 3);

	vector<vector<double>> filter = getGaussianFilter(size);

	Point des{ target.x, target.y };

	double displacementX = static_cast<double>(des.x) - src.x;
	double displacementY = static_cast<double>(des.y) - src.y;

	glPointSize((float)1);
	glBegin(GL_POINTS);
	for (int x = src.x - size / 2, i = 0; x < src.x + size / 2; x++, i++) {
		for (int y = src.y - size / 2, j = 0; y < src.y + size / 2; y++, j++) {
			// check boundary case
			if (x < 0 || x > width - 1 || y < 0 || y > height - 1) {
				continue;
			}
			// eliminate the points outside of the circle brush
			if (Pythagoras(static_cast<double>(x) - src.x, static_cast<double>(y) - src.y) > size / 2) {
				continue;
			}

			double pxX = x - filter[i][j] * displacementX / filter[size / 2][size / 2];
			double pxY = y - filter[i][j] * displacementY / filter[size / 2][size / 2];
			int pixelX = (int)pxX;
			int pixelY = (int)pxY;

			// check boundary again
			if (pixelX < 0 || pixelX > width - 1 || pixelY < 0 || pixelY > height - 1) {
				continue;
			}

			GLubyte color[3];
			color[0] = img[(pixelY * width + pixelX) * 3];
			color[1] = img[(pixelY * width + pixelX) * 3+1];
			color[2] = img[(pixelY * width + pixelX) * 3+2];

			glColor4f(
				(float)color[0] / 255.0f * pDoc->getColorR(),
				(float)color[1] / 255.0f * pDoc->getColorG(),
				(float)color[2] / 255.0f * pDoc->getColorB(),
				(float)pDoc->getAlpha()
			);
			glVertex2d(x, y);
		}
	}
	glEnd();
	pDoc->m_pUI->m_paintView->SaveCurrentContent();
	src = des;
	delete[] img;
}

void WarpBrush::BrushEnd(const Point source, const Point target) {

}

vector<vector<double>> WarpBrush::getGaussianFilter(int size) {
	const double sigma = (size-1)/6;
	vector<vector<double>> res;
	for (int i = 0; i < size; i++) {
		vector<double> temp;
		for (int j = 0; j < size; j++) {
			int x = i - size / 2;
			int y = j - size / 2;
			double val = (1 / (2 * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma));
			temp.push_back(val);
		}
		res.push_back(temp);
	}
	return res;
}
