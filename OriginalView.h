//
// originalview.h
//
// The header file for original view of the input images
//

#ifndef ORIGINALVIEW_H
#define ORIGINALVIEW_H

#include <FL/Fl.H>

#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>

#include "ImpBrush.h"

class ImpressionistDoc;

class OriginalView : public Fl_Gl_Window
{
public:
	OriginalView(int x, int y, int w, int h, const char *l);
	
	void draw();
	void refresh();
	void drawCursor(Point source);
	// int handle(int event);

	void resizeWindow(int width, int height);
	void SaveCurrentContent();
	void RestoreContent();

	ImpressionistDoc*	m_pDoc;

private:
	GLvoid* m_pOrigBitstart;
	Point cursorPos;
	int	m_nWindowWidth;
	int m_nWindowHeight;
	int m_nDrawWidth;
	int m_nDrawHeight;
	int m_nStartRow;
	int m_nStartCol;
	int m_nEndRow;
	int m_nEndCol;
	

};

#endif