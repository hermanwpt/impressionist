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
	GLubyte* applyGaussianFilteratXY(unsigned char* img, int x, int y, const vector<vector<double>>& filter);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

private:
	Point src;
};

#endif // !WARPBRUSH_H
