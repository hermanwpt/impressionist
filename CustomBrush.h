#ifndef CUSTOMBRUSH_H
#define CUSTOMBRUSH_H

#include "ImpBrush.h"
#include <vector>

enum filterType {
	SHARPENING,
	BLUR
};

class CustomBrush : public ImpBrush
{
public:
	CustomBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);

	void selectFilter(filterType type);
	void applyFilter(int x, int y);

	char* BrushName(void);



private:
	std::vector<std::vector<double>> filter;
	int filterSize;
	unsigned char* img = nullptr;
};

#endif
