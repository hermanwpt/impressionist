//
// paintview.h
//
// The header file for painting view of the input images
//

#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <vector>

class ImpressionistDoc;

class PaintView : public Fl_Gl_Window
{
public:
	PaintView(int x, int y, int w, int h, const char* l);
	void draw();
	int handle(int event);

	void refresh();
	
	void resizeWindow(int width, int height);

	void SaveCurrentContent();

	void RestoreContent();


	void setAutoPaint(bool flag);
	void setDissolve(bool flag);
	bool getDissolve();

	void applyFilterKernel(std::vector<std::vector<double>> fk, bool normalized);


	ImpressionistDoc *m_pDoc;

private:
	GLvoid* m_pPaintBitstart;
	int		m_nDrawWidth,
			m_nDrawHeight,
			m_nStartRow, 
			m_nEndRow,
			m_nStartCol, 
			m_nEndCol,
			m_nWindowWidth, 
			m_nWindowHeight;
			
	// For specifiying LINE brush angle & length
	int		m_lStartX;
	int		m_lStartY;
	int		m_lEndX;
	int		m_lEndY;

	// For autopaint
	bool	m_nAuto;

	// For image dissolve
	bool	m_nDissolve;
};

#endif