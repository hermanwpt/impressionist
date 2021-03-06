// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"

#include <vector>

class ImpressionistUI;

class intPair {
public:
	int a, b;

	intPair() {};
	intPair(int aa, int bb) {
		a = aa;
		b = bb;
	};
};

class BFSVertex {
public:
	BFSVertex() {};
	BFSVertex(int xx, int yy, bool d) {
		x = xx;
		y = yy;
		data = d;
		checked = false;
	}
	int x;
	int y;
	bool data;
	bool checked;
};

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);						// called by the UI to load image
	int		loadOtherImage(char* iname, bool mode);		// called by the UI to load edge/another image
	int		loadMuralImage(char* iname);				// called by the UI to load mural image										**BONUS
	int		saveImage(char *iname);						// called by the UI to save image


	int     clearCanvas();						// called by the UI to clear the drawing canvas
	void	setBrushType(int type);				// called by the UI to set the brushType
	void	setStrokeDirectionType(int type);	// called by the UI to set the strokeDirectionType
	void	setPaintlyStyle(int type);			// called by the UI to set the paintlyStyleType
	void	setPaintlyStrokeType(int type);		// called by the UI to set the paintlyStrokeType
	void	undo();								// called by the UI "Undo"															**BONUS
	void	swap();								// swap origView and paintView														**BONUS
	void	saveLastPaint();					// save the painting to m_ucLastPaint after every brush								**BONUS
	void	customizedImageConvolution(std::vector<std::vector<double>> fk, bool normalized);	// apply customized filter kernel	**BONUS

	int		getSize();							// get the UI size
	int		getWidth();
	int		getAngle();
	int		getThreshold();
	int		getStrokeDirectionType();
	int		getBrushType();
	int		getSpacing();
	double	getAlpha();
	double	getColorR();
	double	getColorG();
	double	getColorB();
	bool	getClip();
	bool	getAnotherGradient();
	bool	getSizeRandom();
	void	setSize(int size);					// set the UI size
	char*	getImageName();						// get the current image name
	

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image (and copies of original, edge and another) and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;
	unsigned char*	m_ucOrig;
	unsigned char*	m_ucEdge;
	unsigned char*	m_ucAnother;
	unsigned char*  m_ucLastPaint;

	intPair**		g_ucOrig;
	intPair**		g_ucAnother;
	BFSVertex**		e_ucEdge;	// Stores the edge image, but in 2D array form, updates when getEdge() is called

	// The current active brush.
	ImpBrush*			m_pCurrentBrush;
	int					m_pCurrentBrushType;
	int					m_lDirType;	// Direction type for LINE brush

	// Size of the brush.
	int m_nSize;							

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );
	// Generate the gradient array of the one currently pointed to by m_ucBitmap
	intPair** getGradient();
	// Generate the edge image of the one currently pointed to by m_ucBitmap, also updates e_ucEdge
	unsigned char* getEdge(intPair** gradient);


private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
