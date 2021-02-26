// 
// WarpBrush.cpp
// 
// This implementation has taken reference from 
// - https://www.cs.princeton.edu/courses/archive/fall00/cs426/lectures/warp/warp.pdf
// - http://www.connellybarnes.com/work/class/2016/intro_gfx/lectures/03-Image.pdf
// - https://github.com/cxcxcxcx/imgwarp-opencv
// The idea is newImg[target.x, target.y] = oldImg[source.x, source.y]
// We use Forward Mapping and Gaussian Filter Resampling.

#include "Impressionist.h"
#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "WarpBrush.h"
#include <iostream>

using namespace std;

extern float fraud();

WarpBrush::WarpBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {
}

void WarpBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();

	int size = pDoc->getSize();

	glPointSize((float)size);

	src = Point{ source.x, source.y };

	BrushMove(source, target);
}

void WarpBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();

	int size = pDoc->getSize();
	int width = pDoc->m_nWidth;
	int height = pDoc->m_nHeight;

	unsigned char* img = new unsigned char[width * height * 3];
	memcpy(img, pDoc->m_ucPainting, width * height * 3);

	vector<vector<double>> filter = getGaussianFilter(size);

	Point des{ source.x, source.y };
	int diffX = des.x - src.x;
	int diffY = des.y - src.y;

	//cout << des.x << " " << des.y << endl;
	//cout << src.x << " " << src.y << endl;
	//cout << endl;

	glPointSize((float)1);
	glBegin(GL_POINTS);
	for (int x = src.x - size / 2; x < src.x + size / 2; x++) {
		for (int y = src.y - size / 2; y < src.y + size / 2; y++) {
			GLubyte* color = applyGaussianFilteratXY(img, x, y, filter);
			glColor4f(
				(float)color[0] / 255.0f * pDoc->getColorR(),
				(float)color[1] / 255.0f * pDoc->getColorG(),
				(float)color[2] / 255.0f * pDoc->getColorB(),
				(float)pDoc->getAlpha()
			);
			glVertex2d(x+diffX, y+diffY);
			delete[] color;
		}
	}
	glEnd();
	src = des;
	delete[] img;
}

void WarpBrush::BrushEnd(const Point source, const Point target) {

}

vector<vector<double>> WarpBrush::getGaussianFilter(int size) {
	const double sigma = size / 3;
	double sum = 0;
	vector<vector<double>> res;
	for (int i = 0; i < size; i++) {
		vector<double> temp;
		for (int j = 0; j < size; j++) {
			int x = i - size / 2;
			int y = j - size / 2;
			double val = (1 / (2 * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma));
			temp.push_back(val);
			sum += val;
		}
		res.push_back(temp);
	}
	return res;
}

GLubyte* WarpBrush::applyGaussianFilteratXY(unsigned char* img, int x, int y, const vector<vector<double>>& filter) {
	ImpressionistDoc* pDoc = GetDocument();
	const int width = pDoc->m_nPaintWidth;
	const int height = pDoc->m_nPaintWidth;
	const int filterSize = filter.size();		// Note that the input is already normalized

	double red = 0;
	double green = 0;
	double blue = 0;
	double normalized = 0;
	bool isBorder = false;
	for (int i = 0; i < filterSize; i++) {
		for (int j = 0; j < filterSize; j++) {
			int pixelX = x - filterSize / 2 + i;
			int pixelY = y - filterSize / 2 + j;
			if (pixelX < 0 || pixelX > width - 1 || pixelY < 0 || pixelY > height - 1) {
				//isBorder = true;
				continue;
			}
			normalized += filter[i][j];
			red += img[(pixelY * width + pixelX) * 3] * filter[i][j];
			green += img[(pixelY * width + pixelX) * 3 + 1] * filter[i][j];
			blue += img[(pixelY * width + pixelX) * 3 + 2] * filter[i][j];
		}
	}
	red /= normalized;
	green /= normalized;
	blue /= normalized;
	GLubyte* res = new GLubyte[3];
	//if (isBorder) {
	//	res[0] = 0;
	//	res[1] = 0;
	//	res[2] = 0;
	//}
	//else {
		res[0] = min(255, max(0, red));
		res[1] = min(255, max(0, green));
		res[2] = min(255, max(0, blue));
	//}
	return res;
}
