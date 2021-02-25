//
// ScatteredTriangleBrush.h
//
// The header file for Point Brush. 
//

#ifndef SCATTEREDTRIANGLEBRUSH_H
#define SCATTEREDTRIANGLEBRUSH_H

#include "ImpBrush.h"

class ScatteredTriangleBrush : public ImpBrush
{
public:
	ScatteredTriangleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

private:
	static const int NUM_TRIANGLES = 4;
};

#endif