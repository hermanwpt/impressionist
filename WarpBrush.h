// 
// WarpBrush.h

#ifndef WARPBRUSH_H
#define WARPBRUSH_H

#include "Impressionist.h"
#include "ImpBrush.h"
#include <vector>

using namespace std;

class WarpBrush : public ImpBrush {
public:
	WarpBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	vector<vector<double>> getGaussianFilter(int size);
	vector<double> applyGaussianFilter(unsigned char* img, int x, int y);

	void BrushBegin(const Point source, const Point target) {}
	void BrushMove(const Point source, const Point target) {}
	void BrushEnd(const Point source, const Point target) {}
	char* BrushName(void) {}



	void SetColor(const Point source) {}


};

#endif // !WARPBRUSH_H
