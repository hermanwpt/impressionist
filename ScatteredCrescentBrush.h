//
// ScatteredCrescentBrush.h
//
// The header file for Point Brush. 
//

#ifndef SCATTEREDCRESCENTBRUSH_H
#define SCATTEREDCRESCENTBRUSH_H

#include "ImpBrush.h"

class ScatteredCrescentBrush : public ImpBrush
{
public:
	ScatteredCrescentBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

private:
	static const int NUM_CRESCENTS = 4;
};

#endif