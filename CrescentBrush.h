//
// CrescentBrush.h
//
// The header file for Circle Brush. 
//

#ifndef CRESCENTBRUSH_H
#define CRESCENTBRUSH_H

#include "ImpBrush.h"

class CrescentBrush : public ImpBrush {
public:
	CrescentBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

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