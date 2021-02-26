// 
// WarpBrush.cpp

#include "Impressionist.h"
#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "WarpBrush.h"

extern float fraud();

WarpBrush::WarpBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {
}

vector<vector<double>> WarpBrush::getGaussianFilter(int size) {
	const double sigma = (size - 1) / 6;
	vector<vector<double>> res;
	for (int i = 0; i < size; i++) {
		vector<double> temp;
		for (int j = 0; j < size; j++) {
			int x = i - size / 2;
			int y = j - size / 2;
			temp.push_back((1 / (2 * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma)));
		}
		res.push_back(temp);
	}
	return res;
}

vector<double> WarpBrush::applyGaussianFilter(unsigned char* img, int x, int y) {
	vector<double> a;
	return a;
}