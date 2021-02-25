//
// SpiralBrush.h
//
// The header file for Crescent Brush. 
//

#ifndef SPIRALBRUSH_H
#define SPIRALBRUSH_H

#include "ImpBrush.h"

class SpiralBrush : public ImpBrush {
public:
	SpiralBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

private:
	static const int NUM_SEGMENTS = 360;
	double sinValues[NUM_SEGMENTS];
	double cosValues[NUM_SEGMENTS];
	Point prevloc;
};

#endif