//
// LineBrush.h
//
// The header file for Point Brush. 
//

#ifndef LINEBRUSH_H
#define LINEBRUSH_H

#include "ImpBrush.h"

class LineBrush : public ImpBrush
{
public:
	LineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void drawCursor(const Point source, const Point target);
	char* BrushName(void);

private:
	static const int NUM_SEGMENTS = 360;
	double sinValues[NUM_SEGMENTS];
	double cosValues[NUM_SEGMENTS];
	Point prevloc;
};

#endif