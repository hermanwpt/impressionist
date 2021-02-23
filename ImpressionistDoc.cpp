// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "LineBrush.h"
#include "CircleBrush.h"
#include "ScatteredPointBrush.h"
#include "ScatteredLineBrush.h"
#include "ScatteredCircleBrush.h"


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_ucOrig		= NULL;
	m_ucEdge		= NULL;
	m_ucAnother		= NULL;
	m_ucLastPaint	= NULL;

	g_ucOrig		= NULL;
	e_ucEdge		= NULL;

	m_pCurrentBrushType = BRUSH_POINTS;
	m_lDirType =	STROKE_SLIDER;


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCircleBrush( this, "Scattered Circles" );

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
	m_pCurrentBrushType = type;
}

//---------------------------------------------------------
//	Called by the UI when the user changes the stroke
//	direction type.
//	type: one of the defined stroke direction types.
//---------------------------------------------------------
void ImpressionistDoc::setStrokeDirectionType(int type) {
	//	TODO
	m_lDirType = type;
}

//---------------------------------------------------------
//	Called by the UI when the user changes the paintly
//	style.
//	type: one of the defined paintly styles.
//---------------------------------------------------------
void ImpressionistDoc::setPaintlyStyle(int type) {
	//	TODO
}

//---------------------------------------------------------
//	Called by the UI when the user changes the paintly
//	stroke type.
//	type: one of the defined paintly stroke types.
//---------------------------------------------------------
void ImpressionistDoc::setPaintlyStrokeType(int type) {
	//	TODO
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//---------------------------------------------------------
// Returns the width of the LINE brush.
//---------------------------------------------------------
int ImpressionistDoc::getWidth()
{
	return m_pUI->getWidth();
}

//---------------------------------------------------------
// Returns the angle of the LINE brush.
//---------------------------------------------------------
int ImpressionistDoc::getAngle()
{
	return m_pUI->getAngle();
}

//---------------------------------------------------------
// Returns the threshold for EDGE detection.
//---------------------------------------------------------
int ImpressionistDoc::getThreshold() {
	return m_pUI->getThreshold();
}

//---------------------------------------------------------
// Returns the stroke direction type for LINE brush.
//---------------------------------------------------------
int ImpressionistDoc::getStrokeDirectionType()
{
	return m_lDirType;
}

//---------------------------------------------------------
// Returns the brush type as INT;
//---------------------------------------------------------
int ImpressionistDoc::getBrushType()
{
	return m_pCurrentBrushType;
}

//---------------------------------------------------------
// Returns the alpha value of the brush.
//---------------------------------------------------------
double ImpressionistDoc::getAlpha()
{
	return m_pUI->getAlpha();
}

//---------------------------------------------------------
// Returns whether edge clipping is turned on
//---------------------------------------------------------
bool ImpressionistDoc::getClip() {
	return m_pUI->getClip();
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	unsigned char*	another_data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}
	another_data=readBMP(iname, width, height);

	// Release storage for old gradient image first
	if (g_ucOrig) {
		for (int i = 0; i < m_nWidth; ++i) {
			delete[] g_ucOrig[i];
		}
		delete[] g_ucOrig;
	}
	g_ucOrig = NULL;

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if (m_ucPainting) delete[] m_ucPainting; 
	if (m_ucOrig) delete[] m_ucOrig; 
	if (m_ucEdge) delete[] m_ucEdge;
	if (m_ucAnother) delete[] m_ucAnother; 
	if (m_ucLastPaint) delete[] m_ucLastPaint;
	e_ucEdge = NULL;

	m_ucOrig		= data;
	m_ucBitmap		= m_ucOrig;

	g_ucOrig		= getGradient();
	m_ucEdge		= getEdge(g_ucOrig);	//	TODO: Replace with a function that generates an edge image of data
	m_ucAnother		= another_data;
	
	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	m_ucLastPaint	= new unsigned char[width * height * 3];
	memset(m_ucPainting, 0, width*height*3);
	memset(m_ucLastPaint, 0, width * height * 3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}

//---------------------------------------------------------
//	Load the edge/another image
//	This is called by the UI when the load edge/another
//	image button is pressed.
//		mode = false:	Loads edge image
//		mode = true:	Loads another image
//---------------------------------------------------------
int ImpressionistDoc::loadOtherImage(char *iname, bool mode) {
	//	Try to open the image to read
	unsigned char* data;
	int	width, height;
	bool edgeFlag = false;
	bool anotherFlag = false;

	if ((data=readBMP(iname, width, height)) == NULL) {
		fl_alert("Can't load bitmap file");
		return 0;

	//	Images other than the original must have matching
	//	dimensions with the original image
	} else if ((width != m_nWidth) || (height != m_nHeight)) {
		fl_alert("Different dimension!");
		return 0;
	}

	if (m_ucBitmap == m_ucEdge) {
		edgeFlag = true;
		m_ucBitmap = NULL;
	}
	if (m_ucBitmap == m_ucAnother) {
		anotherFlag = true;
		m_ucBitmap = NULL;
	}

	//	Release old storage and assign new image to variables
	if (mode) {
		if (m_ucAnother) delete[] m_ucAnother;
		m_ucAnother = data;
	} else {
		if (m_ucEdge) delete[] m_ucEdge;
		m_ucEdge = data;
		
		e_ucEdge = new BFSVertex * [width];
		for (int i = 0; i < m_nWidth; ++i) {
			e_ucEdge[i] = new BFSVertex[height];
		}

		for (int i = 0; i < m_nWidth; ++i) {
			for (int j = 0; j < m_nHeight; ++j) {
				int intensity = m_ucEdge[(i + j * width) * 3];
				if (intensity == 0) {
					e_ucEdge[i][j] = BFSVertex(i, j, false);
				} else {
					e_ucEdge[i][j] = BFSVertex(i, j, true);
				}
			}
		}
	}

	if (edgeFlag) {
		m_ucBitmap = m_ucEdge;
	}
	if (anotherFlag) {
		m_ucBitmap = m_ucAnother;
	}

	return 1;
}

//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;
		delete[] m_ucLastPaint;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//------------------------------------------------------------------
// save the painting to m_ucLastPaint after every brush
//------------------------------------------------------------------
void ImpressionistDoc::saveLastPaint() {
	memcpy(m_ucLastPaint, m_ucPainting, m_nWidth * m_nHeight * 3 * sizeof(unsigned char));
}

//------------------------------------------------------------------
// undo the last brush
//------------------------------------------------------------------
void ImpressionistDoc::undo() {
	memcpy(m_ucPainting, m_ucLastPaint, m_nWidth * m_nHeight * 3 * sizeof(unsigned char));
	m_pUI->m_paintView->refresh();
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucOrig + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

int comparator(const void* a, const void* b) {
	return *(GLubyte*)a = *(GLubyte*)b;
}

//----------------------------------------------------------------
//	Generate the gradient array of the one currently pointed to
//	by m_ucBitmap
//----------------------------------------------------------------
intPair** ImpressionistDoc::getGradient() {
	// Convert image to greyscalae
	GLubyte** greyscale = new GLubyte*[m_nWidth];
	for (int i = 0; i < m_nWidth; ++i) {
		greyscale[i] = new GLubyte[m_nHeight];
	}

	for (int i = 0; i < m_nWidth; ++i) {
		for (int j = 0; j < m_nHeight; ++j) {
			GLubyte color[3];
			memcpy(color, GetOriginalPixel(i, j), 3);

			greyscale[i][j] = color[0]; // (GLubyte)(0.299 * color[0] + 0.587 * color[1] + 0.114 * color[2]);	// From tutorial notes
		}
	}

	// Denoise the image with median filter;
	GLubyte** denoisedImage = new GLubyte * [m_nWidth];
	for (int i = 0; i < m_nWidth; ++i) {
		denoisedImage[i] = new GLubyte[m_nHeight];
	}

	for (int i = 1; i < m_nWidth - 1; ++i) {
		for (int j = 1; j < m_nHeight - 1; ++j) {
			GLubyte pixels[9];
			for (int u = 0; u <= 2; ++u) {
				for (int v = 0; v <= 2; ++v) {
					pixels[u * 3 + v] = greyscale[i + u - 1][j + v - 1];
				}
			}
			qsort(pixels, 9, sizeof(GLubyte), comparator);
			denoisedImage[i][j] = pixels[4];
		}
	}

	// Pad the denoised image with new border pixels
	for (int i = 1; i < m_nWidth - 1; ++i) {
		denoisedImage[i][0] = denoisedImage[i][1];
		denoisedImage[i][m_nHeight - 1] = denoisedImage[i][m_nHeight - 2];
	}

	for (int i = 0; i < m_nHeight; ++i) {
		denoisedImage[0][i] = denoisedImage[1][i];
		denoisedImage[m_nWidth - 1][i] = denoisedImage[m_nWidth - 2][i];
	}

	// Calculate gradient using sobel operators
	int offset = 0;

	intPair** gradient = new intPair* [m_nWidth];
	for (int i = 0; i < m_nWidth; ++i) {
		gradient[i] = new intPair[m_nHeight];
	}

	for (int i = 1; i < m_nWidth - 1; ++i) {
		for (int j = 1; j < m_nHeight - 1; ++j) {
			GLubyte pixels[9];
			for (int u = 0; u <= 2; ++u) {
				for (int v = 0; v <= 2; ++v) {
					pixels[u * 3 + v] = denoisedImage[i + u - 1][j + v - 1];
				}
			}
			int xGradient = (int)min((
					-1 * pixels[0] +	 0 * pixels[3] +	 1 * pixels[6]
				+	-2 * pixels[1] +	 0 * pixels[4] +	 2 * pixels[7]
				+	-1 * pixels[2] +	 0 * pixels[5] +	 1 * pixels[8]
				+ offset
			), 32768);
			int yGradient = (int)min((
					 1 * pixels[0] +	 2 * pixels[3] +	 1 * pixels[6]
				+	 0 * pixels[1] +	 0 * pixels[4] +	 0 * pixels[7]
				+	-1 * pixels[2] +	-2 * pixels[5] +	-1 * pixels[8]
				+ offset
			), 32768);
			gradient[i][j] = intPair(xGradient, yGradient);
			// printf("Gradient at (%d, %d) = (%d, %d)\n", i, j, xGradient, yGradient);
		}
	}

	// Pad the denoised image with new border pixels
	for (int i = 1; i < m_nWidth - 1; ++i) {
		gradient[i][0] = intPair(gradient[i][1].a, gradient[i][1].b);
		gradient[i][m_nHeight - 1] = intPair(gradient[i][m_nHeight - 2].a, gradient[i][m_nHeight - 2].b);
	}

	for (int i = 0; i < m_nHeight; ++i) {
		gradient[0][i] = intPair(gradient[1][i].a, gradient[1][i].b);
		gradient[m_nWidth - 1][i] = intPair(gradient[m_nWidth - 2][i].a, gradient[m_nWidth - 2][i].b);
	}

	// Release old storage
	for (int i = 0; i < m_nWidth; ++i) {
		delete [] greyscale[i];
	}
	delete [] greyscale;

	for (int i = 0; i < m_nWidth; ++i) {
		delete[] denoisedImage[i];
	}
	delete[] denoisedImage;

	return gradient;
}

//----------------------------------------------------------------
//	Generate the edge image of the one currently pointed to by
//	m_ucBitmap
//	Also updates e_ucBitmap
//----------------------------------------------------------------
unsigned char* ImpressionistDoc::getEdge(intPair** gradient) {
	// Release storage for old edge image array first
	bool flag = false;
	if (m_ucBitmap == m_ucEdge) {
		flag = true;
	}
	if (e_ucEdge) {
		for (int i = 0; i < m_nWidth; ++i) {
			delete[] e_ucEdge[i];
		}
		delete[] e_ucEdge;
	}
	

	e_ucEdge = new BFSVertex* [m_nWidth];
	for (int i = 0; i < m_nWidth; ++i) {
		e_ucEdge[i] = new BFSVertex[m_nHeight];
	}

	int numBytes = m_nWidth * m_nHeight * 3;
	unsigned char* edgeImage = new unsigned char[numBytes];
	memset(edgeImage, 0, numBytes);

	int threshold = sqrt(1020 * 1020 * 2) * getThreshold() / 1000;

	for (int i = 0; i < m_nWidth; ++i) {
		for (int j = 0; j < m_nHeight; ++j) {
			int intensity = (int)(sqrt(gradient[i][j].a * gradient[i][j].a + gradient[i][j].b * gradient[i][j].b));
			// printf("intensify at (%d, %d) = %d\n", i, j, intensity);
			if (intensity < threshold) {
				edgeImage[(i + j * m_nWidth) * 3] = 0;
				edgeImage[(i + j * m_nWidth) * 3 + 1] = 0;
				edgeImage[(i + j * m_nWidth) * 3 + 2] = 0;
				e_ucEdge[i][j] = BFSVertex(i, j, false);
			} else {
				edgeImage[(i + j * m_nWidth) * 3] = 255;
				edgeImage[(i + j * m_nWidth) * 3 + 1] = 255;
				edgeImage[(i + j * m_nWidth) * 3 + 2] = 255;
				e_ucEdge[i][j] = BFSVertex(i, j, true);
			}
			
		}
	}

	if (flag) {
		m_ucBitmap = edgeImage;
	}

	return edgeImage;
}

