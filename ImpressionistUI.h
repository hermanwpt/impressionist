//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Color_Chooser.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

#include <vector>

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Window*			m_colorsDialog;
	Fl_Window*			m_paintlyDialog;

	Fl_Group*			paintlyCustomizeGroup;

	Fl_Choice*			m_BrushTypeChoice;
	Fl_Choice*			m_StrokeDirectionTypeChoice;
	Fl_Choice*			m_PaintlyStyleChoice;
	Fl_Choice*			m_PaintlyStrokeTypeChoice;

	Fl_Slider*			m_BrushSizeSlider;
	Fl_Slider*			m_LineWidthSlider;
	Fl_Slider*			m_LineAngleSlider;
	Fl_Slider*			m_BrushAlphaSlider;
	Fl_Slider*			m_SpacingSlider;
	Fl_Slider*			m_EdgeThresholdSlider;
	Fl_Slider*			m_PaintlyThresholdSlider;
	Fl_Slider*			m_PaintlyCurvatureSlider;
	Fl_Slider*			m_PaintlyBlurSlider;
	Fl_Slider*			m_PaintlyGridSizeSlider;
	Fl_Slider*			m_PaintlyMinStrokeLSlider;
	Fl_Slider*			m_PaintlyMaxStrokeLSlider;
	Fl_Slider*			m_PaintlyAlphaSlider;
	Fl_Slider*			m_PaintlyLayersSlider;
	Fl_Slider*			m_PaintlyR0LevelSlider;
	Fl_Slider*			m_PaintlyJrSlider;
	Fl_Slider*			m_PaintlyJgSlider;
	Fl_Slider*			m_PaintlyJbSlider;
	Fl_Slider*			m_PaintlyJhSlider;
	Fl_Slider*			m_PaintlyJsSlider;
	Fl_Slider*			m_PaintlyJvSlider;

	Fl_Input*			m_FilterKernelInput;
	Fl_Input*			m_FilterKernelInputSize;

	Fl_Button*          m_ClearCanvasButton;
	Fl_Button*			m_PaintButton;
	Fl_Button*			m_DoItButton;
	Fl_Button*			m_RunButton;
	Fl_Button*			m_FilterKernelApplyButton;
	Fl_Light_Button*	m_EdgeClippingButton;
	Fl_Light_Button*	m_AnotherGradientButton;
	Fl_Light_Button*	m_SizeRandomButton;
	Fl_Light_Button*	m_FilterKernelNormalizeButton;

	Fl_Color_Chooser*	m_ColorChooser;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	int					getWidth();
	int					getAngle();
	int					getThreshold();
	double				getAlpha();
	bool				getClip();
	void				setSize(int size);
	void				setAngle(int angle);
	std::vector<std::vector<double>> getCustomizedFilterKernel();

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here

	// Brush attributes
	int		m_nSize;
	double	m_nColorR;
	double	m_nColorG;
	double	m_nColorB;
	double	m_nAlpha;

	// Line attributes
	int		m_lWidth;
	int		m_lAngle;
	bool	m_lClip;
	bool	m_lAnother;

	// Random paint attributes
	int		m_rSpacing;
	bool	m_rSizeRandom;

	// Edge attributes
	int		m_eThreshold;
	
	// Paintly attributes
	int m_pThreshold;
	int m_pMinStrokeL;
	int m_pMaxStrokeL;
	int m_pLayers;
	int m_pR0Level;
	double m_pCurvature;
	double m_pBlur;
	double m_pGridSize;
	double m_pAlpha;
	double m_pJr;
	double m_pJg;
	double m_pJb;
	double m_pJh;
	double m_pJs;
	double m_pJv;

	// Filter Kernel attributes
	bool m_FilterKernelNormalize;
	char* m_FilterKernelText;
	char* m_FilterKernelSize;
	std::vector<std::vector<double>> m_customizedFilterKernel;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		strokeDirectionTypeMenu[NUM_STROKE_DIRECTION_TYPE+1];
	static Fl_Menu_Item		paintlyStyleMenu[NUM_PAINTLY_STYLE+1];
	static Fl_Menu_Item		paintlyStrokeTypeMenu[NUM_PAINTLY_STROKE_TYPE+1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void cb_load_edge_image(Fl_Menu_* o, void* v);
	static void cb_load_another_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void cb_colors(Fl_Menu_* o, void* v);
	static void cb_paintly(Fl_Menu_* o, void* v);
	static void cb_undo(Fl_Menu_* o, void* v);
	static void cb_swap(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void cb_original_image(Fl_Menu_* o, void* v);
	static void cb_edge_image(Fl_Menu_* o, void* v);
	static void cb_another_image(Fl_Menu_* o, void* v);
	static void cb_faster(Fl_Menu_* o, void* v);
	static void cb_safer(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);

	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void cb_strokeDirectionTypeChoice(Fl_Widget* o, void* v);
	static void cb_paintlyStyleChoice(Fl_Widget* o, void* v);
	static void cb_paintlyStrokeTypeChoice(Fl_Widget* o, void* v);

	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void cb_edge_clipping_button(Fl_Widget* o, void* v);
	static void cb_another_gradient_button(Fl_Widget* o, void* v);
	static void cb_size_random_button(Fl_Widget* o, void* v);
	static void cb_paint_button(Fl_Widget* o, void* v);
	static void cb_do_it_button(Fl_Widget* o, void* v);
	static void cb_run_button(Fl_Widget* o, void* v);
	static void cb_filterkernelsize(Fl_Widget* o, void* v);
	static void cb_filterkernelinput(Fl_Widget* o, void* v);
	static void cb_filterkernelapply(Fl_Widget* o, void* v);
	static void cb_filterkernelnormalize(Fl_Widget* o, void* v);

	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void cb_widthSlides(Fl_Widget* o, void* v);
	static void cb_angleSlides(Fl_Widget* o, void* v);
	static void cb_alphaSlides(Fl_Widget* o, void* v);
	static void cb_spacingSlides(Fl_Widget* o, void* v);
	static void cb_thresholdSlides(Fl_Widget* o, void* v);
	static void cb_paintlyThresholdSlides(Fl_Widget* o, void* v);
	static void cb_paintlyCurvatureSlides(Fl_Widget* o, void* v);
	static void cb_paintlyBlurSlides(Fl_Widget* o, void* v);
	static void cb_paintlyGridSizeSlides(Fl_Widget* o, void* v);
	static void cb_paintlyMinStrokeLSlides(Fl_Widget* o, void* v);
	static void cb_paintlyMaxStrokeLSlides(Fl_Widget* o, void* v);
	static void cb_paintlyAlphaSlides(Fl_Widget* o, void* v);
	static void cb_paintlyLayersSlides(Fl_Widget* o, void* v);
	static void cb_paintlyR0LevelSlides(Fl_Widget* o, void* v);
	static void cb_paintlyJrSlides(Fl_Widget* o, void* v);
	static void cb_paintlyJgSlides(Fl_Widget* o, void* v);
	static void cb_paintlyJbSlides(Fl_Widget* o, void* v);
	static void cb_paintlyJhSlides(Fl_Widget* o, void* v);
	static void cb_paintlyJsSlides(Fl_Widget* o, void* v);
	static void cb_paintlyJvSlides(Fl_Widget* o, void* v);

	static void cb_colorChooser(Fl_Widget* o, void* v);
};

#endif
