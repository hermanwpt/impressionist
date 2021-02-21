// 
// WarpBrush.h

#ifndef WARPBRUSH_H
#define WARPBRUSH_H

#include "ImpBrush.h"

class WarpBrush : public ImpBrush {
public:
	WarpBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target) {}
	void BrushMove(const Point source, const Point target) {}
	void BrushEnd(const Point source, const Point target) {}
	char* BrushName(void) {}

	void SetColor(const Point source) {}


};

#endif // !WARPBRUSH_H
