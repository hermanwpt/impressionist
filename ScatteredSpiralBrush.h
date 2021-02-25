//
// ScatteredSpiralBrush.h
//
// The header file for Point Brush. 
//

#ifndef SCATTEREDSPIRALBRUSH_H
#define SCATTEREDSPIRALBRUSH_H

#include "ImpBrush.h"

class ScatteredSpiralBrush : public ImpBrush
{
public:
	ScatteredSpiralBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

private:
	static const int NUM_SPIRALS = 4;
};

#endif