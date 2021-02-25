//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>
#include <sstream>
#include <iostream>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}

//-------------------------------------------------------------
//	Brings up a file chooser and then loads the chosen image
//	This is called by the UI when the load edge image menu item
//	is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_load_edge_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadOtherImage(newfile, false);
	}
}

//-------------------------------------------------------------
//	Brings up a file chooser and then loads the chosen image
//	This is called by the UI when the load another image menu
//	item is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_load_another_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadOtherImage(newfile, true);
	}
}

void ImpressionistUI::cb_load_mural_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadMuralImage(newfile);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//-------------------------------------------------------------
//	Brings up the colors dialog
//	This is called by the UI when the colors menu item is
//	chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_colors(Fl_Menu_* o, void* v) {
	whoami(o)->m_colorsDialog->show();
}

//-------------------------------------------------------------
//	Brings up the auto paint dialog
//	This is called by the UI when the paintly menu item is
//	chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_paintly(Fl_Menu_* o, void* v) {
	whoami(o)->m_paintlyDialog->show();
}

//-------------------------------------------------------------
//	Undo last brush
//-------------------------------------------------------------
void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	pDoc->undo();
}

//-------------------------------------------------------------
//	swap origView and paintView
//-------------------------------------------------------------
void ImpressionistUI::cb_swap(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	pDoc->swap();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();
	whoami(o)->m_colorsDialog->hide();
	whoami(o)->m_paintlyDialog->hide();

}

//-----------------------------------------------------------
//	Shows the original image on the left
//	Called by the UI when the original image menu item is
//	chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_original_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	pDoc->m_ucBitmap = pDoc->m_ucOrig;
	whoami(o)->m_origView->refresh();
}

//-----------------------------------------------------------
//	Shows the edge image on the left
//	Called by the UI when the edge image menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_edge_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	pDoc->m_ucBitmap = pDoc->m_ucEdge;
	whoami(o)->m_origView->refresh();
}

//-----------------------------------------------------------
//	Shows the another image on the left
//	Called by the UI when the another image menu item is
//	chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_another_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	pDoc->m_ucBitmap = pDoc->m_ucAnother;
	whoami(o)->m_origView->refresh();
}

//-----------------------------------------------------------
//	I haven't figured out what this does yet
//	Called by the UI when the faster menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_faster(Fl_Menu_* o, void* v) {
	//	TODO
}

//-----------------------------------------------------------
//	I haven't figured out what this does yet
//	Called by the UI when the safer menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_safer(Fl_Menu_* o, void* v) {
	//	TODO
}

//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

void ImpressionistUI::cb_dissolve(Fl_Menu_* o, void* v)
{
	whoami(o)->m_paintView->setDissolve(true);
	whoami(o)->m_paintView->refresh();
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;

	pDoc->setBrushType(type);

	// Enable/disable certain options whenever appropriate
	if ((type == BRUSH_LINES) || (type == BRUSH_SCATTERED_LINES)
		|| (type == BRUSH_CRESCENTS) || (type == BRUSH_SCATTERED_CRESCENTS)
		|| (type == BRUSH_TRIANGLES) || (type == BRUSH_SCATTERED_TRIANGLES)) {
		pUI->m_StrokeDirectionTypeChoice->activate();
		pUI->m_LineWidthSlider->activate();
		pUI->m_LineAngleSlider->activate();
		pUI->m_AnotherGradientButton->activate();

		if ((type == BRUSH_CRESCENTS) || (type == BRUSH_SCATTERED_CRESCENTS)
			|| (type == BRUSH_TRIANGLES) || (type == BRUSH_SCATTERED_TRIANGLES)) {
			pUI->m_LineWidthSlider->deactivate();
		}
	}
	else {
		pUI->m_StrokeDirectionTypeChoice->deactivate();
		pUI->m_LineWidthSlider->deactivate();
		pUI->m_LineAngleSlider->deactivate();
		pUI->m_AnotherGradientButton->deactivate();
	}


	if (type != BRUSH_SCATTERED_POINTS) {
		pUI->m_EdgeClippingButton->activate();
	}
	else {
		pUI->m_EdgeClippingButton->deactivate();
	}
	
	
}

//-------------------------------------------------------------
//	Sets the type of stroke direction to use to the one chosen
//	in the stroke direction choice
//	Called by the UI when a stroke direction is chosen in the
//	stroke direction choice
//-------------------------------------------------------------
void ImpressionistUI::cb_strokeDirectionTypeChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;

	pDoc->setStrokeDirectionType(type);
}

//-------------------------------------------------------------
//	Sets the paintly style to use to the one chosen in the
//	paintly style choice
//	Called by the UI when a style is chosen in the paintly
//	style choice
//-------------------------------------------------------------
void ImpressionistUI::cb_paintlyStyleChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;

	pDoc->setPaintlyStyle(type);

	// Update UI according to the selected style
	switch (type) {
	case STYLE_IMPRESSIONIST:
		pUI->m_PaintlyThresholdSlider->value(100);
		pUI->m_PaintlyCurvatureSlider->value(1.00);
		pUI->m_PaintlyBlurSlider->value(0.50);
		pUI->m_PaintlyGridSizeSlider->value(1.00);
		pUI->m_PaintlyMinStrokeLSlider->value(4);
		pUI->m_PaintlyMaxStrokeLSlider->value(16);
		pUI->m_PaintlyAlphaSlider->value(1.00);
		pUI->m_PaintlyLayersSlider->value(3);
		pUI->m_PaintlyR0LevelSlider->value(3);
		pUI->m_PaintlyJrSlider->value(0.00);
		pUI->m_PaintlyJgSlider->value(0.00);
		pUI->m_PaintlyJbSlider->value(0.00);
		pUI->m_PaintlyJhSlider->value(0.00);
		pUI->m_PaintlyJsSlider->value(0.00);
		pUI->m_PaintlyJvSlider->value(0.00);
		break;

	case STYLE_EXPRESSIONIST:
		pUI->m_PaintlyThresholdSlider->value(50);
		pUI->m_PaintlyCurvatureSlider->value(0.25);
		pUI->m_PaintlyBlurSlider->value(0.50);
		pUI->m_PaintlyGridSizeSlider->value(1.00);
		pUI->m_PaintlyMinStrokeLSlider->value(10);
		pUI->m_PaintlyMaxStrokeLSlider->value(16);
		pUI->m_PaintlyAlphaSlider->value(0.70);
		pUI->m_PaintlyLayersSlider->value(3);
		pUI->m_PaintlyR0LevelSlider->value(3);
		pUI->m_PaintlyJrSlider->value(0.00);
		pUI->m_PaintlyJgSlider->value(0.00);
		pUI->m_PaintlyJbSlider->value(0.00);
		pUI->m_PaintlyJhSlider->value(0.00);
		pUI->m_PaintlyJsSlider->value(0.00);
		pUI->m_PaintlyJvSlider->value(0.50);
		break;

	case STYLE_COLOR_WASH:
		pUI->m_PaintlyThresholdSlider->value(200);
		pUI->m_PaintlyCurvatureSlider->value(1.00);
		pUI->m_PaintlyBlurSlider->value(0.50);
		pUI->m_PaintlyGridSizeSlider->value(1.00);
		pUI->m_PaintlyMinStrokeLSlider->value(4);
		pUI->m_PaintlyMaxStrokeLSlider->value(16);
		pUI->m_PaintlyAlphaSlider->value(0.50);
		pUI->m_PaintlyLayersSlider->value(3);
		pUI->m_PaintlyR0LevelSlider->value(3);
		pUI->m_PaintlyJrSlider->value(0.30);
		pUI->m_PaintlyJgSlider->value(0.30);
		pUI->m_PaintlyJbSlider->value(0.30);
		pUI->m_PaintlyJhSlider->value(0.00);
		pUI->m_PaintlyJsSlider->value(0.00);
		pUI->m_PaintlyJvSlider->value(0.00);
		break;

	case STYLE_POINTILLIST:
		pUI->m_PaintlyThresholdSlider->value(100);
		pUI->m_PaintlyCurvatureSlider->value(1.00);
		pUI->m_PaintlyBlurSlider->value(0.50);
		pUI->m_PaintlyGridSizeSlider->value(1.00);
		pUI->m_PaintlyMinStrokeLSlider->value(0);
		pUI->m_PaintlyMaxStrokeLSlider->value(0);
		pUI->m_PaintlyAlphaSlider->value(1.00);
		pUI->m_PaintlyLayersSlider->value(2);
		pUI->m_PaintlyR0LevelSlider->value(2);
		pUI->m_PaintlyJrSlider->value(0.00);
		pUI->m_PaintlyJgSlider->value(0.00);
		pUI->m_PaintlyJbSlider->value(0.00);
		pUI->m_PaintlyJhSlider->value(0.30);
		pUI->m_PaintlyJsSlider->value(0.00);
		pUI->m_PaintlyJvSlider->value(1.00);
		break;

	default:
		break;
	}

	// Update attributes
	pUI->m_PaintlyThresholdSlider->do_callback();
	pUI->m_PaintlyCurvatureSlider->do_callback();
	pUI->m_PaintlyBlurSlider->do_callback();
	pUI->m_PaintlyGridSizeSlider->do_callback();
	pUI->m_PaintlyMinStrokeLSlider->do_callback();
	pUI->m_PaintlyMaxStrokeLSlider->do_callback();
	pUI->m_PaintlyAlphaSlider->do_callback();
	pUI->m_PaintlyLayersSlider->do_callback();
	pUI->m_PaintlyR0LevelSlider->do_callback();
	pUI->m_PaintlyJrSlider->do_callback();
	pUI->m_PaintlyJgSlider->do_callback();
	pUI->m_PaintlyJbSlider->do_callback();
	pUI->m_PaintlyJhSlider->do_callback();
	pUI->m_PaintlyJsSlider->do_callback();
	pUI->m_PaintlyJvSlider->do_callback();

	// Enable/disable certain options whenever appropriate
	if (type == STYLE_CUSTOMIZE) {
		pUI->m_PaintlyStrokeTypeChoice->activate();
		pUI->paintlyCustomizeGroup->activate();
	}
	else {
		pUI->m_PaintlyStrokeTypeChoice->deactivate();
		pUI->paintlyCustomizeGroup->deactivate();
	}
}

//-------------------------------------------------------------
//	Sets the paintly stroke type to use to the one chosen in
//	the paintly stroke type choice
//	Called by the UI when a stroke type is chosen in the
//	paintly stroke type choice
//-------------------------------------------------------------
void ImpressionistUI::cb_paintlyStrokeTypeChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;

	pDoc->setPaintlyStrokeType(type);
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
//	Toggles edge clipping for line brushes
//	Called by the UI when the edge clipping button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_edge_clipping_button(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_lClip = bool(((Fl_Button*)o)->value());
}

//------------------------------------------------------------
//	Toggles another gradient for line brushes
//	Called by the UI when the another gradient button is
//	pushed
//------------------------------------------------------------
void ImpressionistUI::cb_another_gradient_button(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_lAnother = bool(((Fl_Button*)o)->value());
}

//------------------------------------------------------------
//	Toggles random brush size for random paint
//	Called by the UI when the size random button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_size_random_button(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_rSizeRandom = bool(((Fl_Button*)o)->value());
}

//------------------------------------------------------------
//	Randomly paints the paintview canvas
//	Called by the UI when the paint button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_paint_button(Fl_Widget* o, void* v) {
	//	TODO
	((ImpressionistUI*)(o->user_data()))->m_paintView->setAutoPaint(true);
	((ImpressionistUI*)(o->user_data()))->m_paintView->refresh();
}

//------------------------------------------------------------
//	Paints the edge image in originalview canvas
//	Called by the UI when the do it button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_do_it_button(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = (ImpressionistUI*)(o->user_data());
	ImpressionistDoc* pDoc = pUI->getDocument();

	if (pDoc->m_ucEdge) delete[] pDoc->m_ucEdge;

	pDoc->m_ucEdge = pDoc->getEdge(pDoc->g_ucOrig);
	pUI->m_origView->refresh();
}

//------------------------------------------------------------
//	Paints the paintly image in paintview canvas
//	Called by the UI when the run button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_run_button(Fl_Widget* o, void* v) {
	//	TODO
}

//------------------------------------------------------------
//	Implement Customized Filter Kernel
//------------------------------------------------------------
void ImpressionistUI::cb_filterkernelsize(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = (ImpressionistUI*)(o->user_data());
	strcpy(pUI->m_FilterKernelSize, ((Fl_Input*)o)->value());
}

void ImpressionistUI::cb_filterkernelinput(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = (ImpressionistUI*)(o->user_data());
	strcpy(pUI->m_FilterKernelText, ((Fl_Input*)o)->value());
}

void ImpressionistUI::cb_filterkernelapply(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = (ImpressionistUI*)(o->user_data());

	pUI->m_customizedFilterKernel.clear();
	if ((pUI->m_FilterKernelSize != nullptr) && (pUI->m_FilterKernelSize[0] == '\0') || (pUI->m_FilterKernelText != nullptr) && (pUI->m_FilterKernelText[0] == '\0')) { // boundary case
		return;
	}
	int size = atoi(pUI->m_FilterKernelSize);			// checked above
	std::stringstream iss(pUI->m_FilterKernelText);		// checked above
	for (int i = 0; i < size; i++) {
		std::vector<double> x;
		for (int j = 0; j < size; j++) {
			double val;
			if (!(iss >> val))
				return;
			x.push_back(val);
		}
		pUI->m_customizedFilterKernel.push_back(x);
	}
	pUI->m_paintView->applyFilterKernel(pUI->m_customizedFilterKernel, pUI->m_FilterKernelNormalize);
}

void ImpressionistUI::cb_filterkernelnormalize(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_FilterKernelNormalize = bool(((Fl_Button*)o)->value());
}

//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
//	Updates the line width to use from the value of the line
//	width slider
//	Called by the UI when the line width slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_widthSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_lWidth = int(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the line angle to use from the value of the line
//	angle slider
//	Called by the UI when the line angle slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_angleSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_lAngle = int(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the brush alpha to use from the value of the
//	brush alpha slider
//	Called by the UI when the brush alpha slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nAlpha = double(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the brush spacing to use from the value of the
//	brush spacing slider in random paint
//	Called by the UI when the spacing slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_spacingSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_rSpacing = int(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the edge threshold to use from the value of the
//	edge threshold slider
//	Called by the UI when the edge threshold slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_thresholdSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_eThreshold = int(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the threshold to use from the value of the
//	paintly threshold slider
//	Called by the UI when the threshold slider is moved in
//	the paintly dialog
//-----------------------------------------------------------
void ImpressionistUI::cb_paintlyThresholdSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pThreshold = int(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the curvature to use from the value of the
//	paintly curvature slider
//	Called by the UI when the curvature slider is moved in
//	the paintly dialog
//-----------------------------------------------------------
void ImpressionistUI::cb_paintlyCurvatureSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pCurvature = double(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the blur to use from the value of the paintly
//	blur slider
//	Called by the UI when the blur slider is moved in the
//	paintly dialog
//-----------------------------------------------------------
void ImpressionistUI::cb_paintlyBlurSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pBlur = double(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the grid size to use from the value of the
//	paintly grid size slider
//	Called by the UI when the grid size slider is moved in
//	the paintly dialog
//-----------------------------------------------------------
void ImpressionistUI::cb_paintlyGridSizeSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pGridSize = double(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the minStrokeL to use from the value of the
//	paintly minStrokeL slider
//	Called by the UI when the minStrokeL slider is moved in
//	the paintly dialog
//-----------------------------------------------------------
void ImpressionistUI::cb_paintlyMinStrokeLSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pMinStrokeL = int(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the maxStrokeL to use from the value of the
//	paintly maxStrokeL slider
//	Called by the UI when the maxStrokeL slider is moved in
//	the paintly dialog
//-----------------------------------------------------------
void ImpressionistUI::cb_paintlyMaxStrokeLSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pMaxStrokeL = int(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the alpha to use from the value of the paintly
//	alpha slider
//	Called by the UI when the alpha slider is moved in the
//	paintly dialog
//-----------------------------------------------------------
void ImpressionistUI::cb_paintlyAlphaSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pAlpha = double(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the layers to use from the value of the paintly
//	layers slider
//	Called by the UI when the layers slider is moved in the
//	paintly dialog
//-----------------------------------------------------------
void ImpressionistUI::cb_paintlyLayersSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pLayers = int(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	Updates the R0 level to use from the value of the paintly
//	R0 level slider
//	Called by the UI when the R0 level slider is moved in the
//	paintly dialog
//-----------------------------------------------------------
void ImpressionistUI::cb_paintlyR0LevelSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pR0Level = int(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
//	The following 6 callbacks updates the colors to use from
//	the value of the paintly color sliders
//	(Jr, Jg, Jb, Jh, Js, Jv)
//	Called by the UI when the corresponding slider is moved
//	in the paintly dialog
//-----------------------------------------------------------
void ImpressionistUI::cb_paintlyJrSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pJr = double(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_paintlyJgSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pJg = double(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_paintlyJbSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pJb = double(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_paintlyJhSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pJh = double(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_paintlyJsSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pJs = double(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_paintlyJvSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_pJv = double(((Fl_Slider*)o)->value());
}



//-----------------------------------------------------------
//	Updates the brush R, G, B colors to use from the value of the
//	color chooser
//	Called by the UI when the color chooser is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_colorChooser(Fl_Widget * o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nColorR = double(((Fl_Color_Chooser*)o)->r());
	((ImpressionistUI*)(o->user_data()))->m_nColorG = double(((Fl_Color_Chooser*)o)->g());
	((ImpressionistUI*)(o->user_data()))->m_nColorB = double(((Fl_Color_Chooser*)o)->b());
}

//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//------------------------------------------------
// Return the LINE brush width
//------------------------------------------------
int ImpressionistUI::getWidth()
{
	return m_lWidth;
}

//------------------------------------------------
// Return the LINE brush angle
//------------------------------------------------
int ImpressionistUI::getAngle()
{
	return m_lAngle;
}

//------------------------------------------------
// Return the EDGE detection threshold
//------------------------------------------------
int ImpressionistUI::getThreshold()
{
	return m_eThreshold;
}

int ImpressionistUI::getSpacing()
{
	return m_rSpacing;
}

//------------------------------------------------
// Return the brush alpha value
//------------------------------------------------
double ImpressionistUI::getAlpha()
{
	return m_nAlpha;
}

double ImpressionistUI::getColorR()
{
	return m_nColorR;;
}

double ImpressionistUI::getColorG()
{
	return m_nColorG;
}

double ImpressionistUI::getColorB()
{
	return m_nColorB;
}

//------------------------------------------------
//	Return the LINE (or other) brush clipping
//	option (TRUE?/FASLE)
//------------------------------------------------
bool ImpressionistUI::getClip()
{
	return m_lClip;
}

bool ImpressionistUI::getAnotherGradient()
{
	return m_lAnother;
}

bool ImpressionistUI::getSizeRandom()
{
	return m_rSizeRandom;
}

//------------------------------------------------
//	Set LINE brush'as angle;
//------------------------------------------------
void ImpressionistUI::setAngle(int angle) {
	m_lAngle = angle;

	if ((angle >= 0) && (angle <= 359))
		m_LineAngleSlider->value(m_lAngle);
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
}

std::vector<std::vector<double>> ImpressionistUI::getCustomizedFilterKernel() {
	return m_customizedFilterKernel;
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback*)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback*)ImpressionistUI::cb_brushes },
		{ "&Clear Canvas",	FL_ALT + 'c', (Fl_Callback*)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },

		{ "&Colors...",					FL_ALT + 'k', (Fl_Callback*)ImpressionistUI::cb_colors },
		{ "&Paintly...",				FL_ALT + 'p', (Fl_Callback*)ImpressionistUI::cb_paintly, 0 },
		{ "&Dissolve Another Image",	FL_ALT + 'd', (Fl_Callback*)ImpressionistUI::cb_dissolve, 0, FL_MENU_DIVIDER },

		{ "&Swap...",		FL_ALT + 'w', (Fl_Callback*)ImpressionistUI::cb_swap },
		{ "&Undo",			FL_ALT + 'z', (Fl_Callback*)ImpressionistUI::cb_undo, 0, FL_MENU_DIVIDER },

		{ "&Load Edge Image...",	FL_ALT + 'e', (Fl_Callback*)ImpressionistUI::cb_load_edge_image },
		{ "&Load Another Image...",	FL_ALT + 'a', (Fl_Callback*)ImpressionistUI::cb_load_another_image },
		{ "&Load Mural Image...",	FL_ALT + 'm', (Fl_Callback*)ImpressionistUI::cb_load_mural_image, 0, FL_MENU_DIVIDER },

		{ "&Quit",			FL_ALT + 'q', (Fl_Callback*)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Display",	0, 0, 0, FL_SUBMENU },
		{ "&Original Image",	FL_ALT + 'o', (Fl_Callback*)ImpressionistUI::cb_original_image },
		{ "&Edge Image",		FL_ALT + 'e', (Fl_Callback*)ImpressionistUI::cb_edge_image },
		{ "&Another Image",		FL_ALT + 'a', (Fl_Callback*)ImpressionistUI::cb_another_image },
		{ 0 },

	{ "&Options",	0, 0, 0, FL_SUBMENU },
		{ "&Faster",	FL_ALT + 'f', (Fl_Callback*)ImpressionistUI::cb_faster },
		{ "&Safer",		FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_safer },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",				FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",					FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",				FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Crescents",				FL_ALT + 'r', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_CRESCENTS},
  {"Triangles",				FL_ALT + 't', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_TRIANGLES},
  {"Spirals",				FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_SPIRALS},
  {"Scattered Points",		FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",		FL_ALT + 'm', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",		FL_ALT + 'd', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Scattered Crescents",	FL_ALT + 'a', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_SCATTERED_CRESCENTS},
  {"Scattered Triangles",	FL_ALT + 'i', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_SCATTERED_TRIANGLES},
  {"Scatttered Spirals",	FL_ALT + 'g', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_SCATTERED_SPIRALS},
  {0}
};

// Stroke direction choice menu definition
Fl_Menu_Item ImpressionistUI::strokeDirectionTypeMenu[NUM_STROKE_DIRECTION_TYPE + 1] = {
	{"Slider/Right Mouse",	FL_ALT + 's',	(Fl_Callback*)ImpressionistUI::cb_strokeDirectionTypeChoice, (void*)STROKE_SLIDER},
	{"Gradient",			FL_ALT + 'g',	(Fl_Callback*)ImpressionistUI::cb_strokeDirectionTypeChoice, (void*)STROKE_GRADIENT},
	{"Brush Direction",		FL_ALT + 'b',	(Fl_Callback*)ImpressionistUI::cb_strokeDirectionTypeChoice, (void*)STROKE_BRUSH_DIRECTION},
	{0}
};

// Paintly style choice menu definition
Fl_Menu_Item ImpressionistUI::paintlyStyleMenu[NUM_PAINTLY_STYLE + 1] = {
	{"Impressionist",	FL_ALT + 'i',	(Fl_Callback*)ImpressionistUI::cb_paintlyStyleChoice, (void*)STYLE_IMPRESSIONIST},
	{"Expressionist",	FL_ALT + 'e',	(Fl_Callback*)ImpressionistUI::cb_paintlyStyleChoice, (void*)STYLE_EXPRESSIONIST},
	{"Color Wash",		FL_ALT + 'w',	(Fl_Callback*)ImpressionistUI::cb_paintlyStyleChoice, (void*)STYLE_COLOR_WASH},
	{"Pointillist",		FL_ALT + 'p',	(Fl_Callback*)ImpressionistUI::cb_paintlyStyleChoice, (void*)STYLE_POINTILLIST},
	{"Customize",		FL_ALT + 'c',	(Fl_Callback*)ImpressionistUI::cb_paintlyStyleChoice, (void*)STYLE_CUSTOMIZE},
	{0}
};

// Paintly stroke type choice menu definition
Fl_Menu_Item ImpressionistUI::paintlyStrokeTypeMenu[NUM_PAINTLY_STYLE + 1] = {
	{"Curve Brush",		FL_ALT + 'r',	(Fl_Callback*)ImpressionistUI::cb_paintlyStrokeTypeChoice, (void*)STROKE_CURVE_BRUSH},
	{"BSpline Brush",	FL_ALT + 'b',	(Fl_Callback*)ImpressionistUI::cb_paintlyStrokeTypeChoice, (void*)STROKE_BSPLINE_BRUSH},
	{"Circle Brush",	FL_ALT + 'c',	(Fl_Callback*)ImpressionistUI::cb_paintlyStrokeTypeChoice, (void*)STROKE_CIRCLE_BRUSH},
	{"Clip Line Brush",	FL_ALT + 'p',	(Fl_Callback*)ImpressionistUI::cb_paintlyStrokeTypeChoice, (void*)STROKE_CLIP_LINE_BRUSH},
	{"Line Brush",		FL_ALT + 'l',	(Fl_Callback*)ImpressionistUI::cb_paintlyStrokeTypeChoice, (void*)STROKE_LINE_BRUSH},
	{0}
};



//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view windows
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_lWidth = 1;
	m_lAngle = 0;
	m_rSpacing = 4;
	m_eThreshold = 200;
	m_nColorR = 1.00;
	m_nColorG = 1.00;
	m_nColorB = 1.00;
	m_nAlpha = 1.00;
	m_lClip = false;
	m_lAnother = false;
	m_rSizeRandom = true;
	m_FilterKernelNormalize = false;
	m_FilterKernelText = new char[255];
	memset(m_FilterKernelText, 0, 255);
	m_FilterKernelSize = new char[255];
	memset(m_FilterKernelSize, 0, 255);
	m_pThreshold = 100;
	m_pCurvature = 1.00;
	m_pBlur = 0.50;
	m_pGridSize = 1.00;
	m_pMinStrokeL = 4;
	m_pMaxStrokeL = 16;
	m_pAlpha = 1.00;
	m_pLayers = 3;
	m_pR0Level = 3;
	m_pJr = 0.00;
	m_pJg = 0.00;
	m_pJb = 0.00;
	m_pJh = 0.00;
	m_pJs = 0.00;
	m_pJv = 0.00;

	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 370, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		// Add clear canvas button to the dialog
		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);

		// Add a stroke direction choice to the dialog
		m_StrokeDirectionTypeChoice = new Fl_Choice(110, 45, 150, 25, "&Stroke Direction");
		m_StrokeDirectionTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_StrokeDirectionTypeChoice->menu(strokeDirectionTypeMenu);
		m_StrokeDirectionTypeChoice->callback(cb_strokeDirectionTypeChoice);
		m_StrokeDirectionTypeChoice->deactivate();

		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Add line width slider to the dialog
		m_LineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
		m_LineWidthSlider->labelfont(FL_COURIER);
		m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_lWidth);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->callback(cb_widthSlides);
		m_LineWidthSlider->deactivate();

		// Add line angle slider to the dialog
		m_LineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
		m_LineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
		m_LineAngleSlider->labelfont(FL_COURIER);
		m_LineAngleSlider->labelsize(12);
		m_LineAngleSlider->minimum(0);
		m_LineAngleSlider->maximum(360);
		m_LineAngleSlider->step(1);
		m_LineAngleSlider->value(m_lAngle);
		m_LineAngleSlider->align(FL_ALIGN_RIGHT);
		m_LineAngleSlider->callback(cb_angleSlides);
		m_LineAngleSlider->deactivate();

		// Add alpha slider to the dialog
		m_BrushAlphaSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		m_BrushAlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushAlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_BrushAlphaSlider->labelfont(FL_COURIER);
		m_BrushAlphaSlider->labelsize(12);
		m_BrushAlphaSlider->minimum(0.00);
		m_BrushAlphaSlider->maximum(1.00);
		m_BrushAlphaSlider->step(0.01);
		m_BrushAlphaSlider->value(m_nAlpha);
		m_BrushAlphaSlider->align(FL_ALIGN_RIGHT);
		m_BrushAlphaSlider->callback(cb_alphaSlides);

		// Add edge clipping button to the dialog
		m_EdgeClippingButton = new Fl_Light_Button(10, 200, 120, 25, "&Edge Clipping");
		m_EdgeClippingButton->value(m_lClip);
		m_EdgeClippingButton->user_data((void*)(this));	// record self to be used by static callback functions
		m_EdgeClippingButton->callback(cb_edge_clipping_button);

		// Add another gradient button to the dialog
		m_AnotherGradientButton = new Fl_Light_Button(240, 200, 150, 25, "&Another Gradient");
		m_AnotherGradientButton->value(m_lAnother);
		m_AnotherGradientButton->user_data((void*)(this));	// record self to be used by static callback functions
		m_AnotherGradientButton->callback(cb_another_gradient_button);
		m_AnotherGradientButton->deactivate();

		// Create a group that will hold the slider and buttons for random paint
		Fl_Group* randomPaintGroup = new Fl_Group(10, 230, 380, 40);
		randomPaintGroup->box(FL_THIN_UP_BOX);
			// Add spacing slider to the group
			m_SpacingSlider = new Fl_Value_Slider(20, 240, 140, 20, "Spacing");
			m_SpacingSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_SpacingSlider->type(FL_HOR_NICE_SLIDER);
			m_SpacingSlider->labelfont(FL_COURIER);
			m_SpacingSlider->labelsize(12);
			m_SpacingSlider->minimum(1);
			m_SpacingSlider->maximum(16);
			m_SpacingSlider->step(1);
			m_SpacingSlider->value(m_rSpacing);
			m_SpacingSlider->align(FL_ALIGN_RIGHT);
			m_SpacingSlider->callback(cb_spacingSlides);
			
			// Add size random button to the group
			m_SizeRandomButton = new Fl_Light_Button(220, 240, 100, 22, "&Size Rand.");
			m_SizeRandomButton->value(m_rSizeRandom);
			m_SizeRandomButton->user_data((void*)(this));	// record self to be used by static callback functions
			m_SizeRandomButton->callback(cb_size_random_button);

			// Add paint button to the group
			m_PaintButton = new Fl_Button(330, 240, 50, 22, "&Paint");
			m_PaintButton->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintButton->callback(cb_paint_button);
		randomPaintGroup->end();

		// Create a group that will hold the slider and button for edge threshold
		Fl_Group* edgeThresholdGroup = new Fl_Group(10, 275, 380, 40);
		edgeThresholdGroup->box(FL_THIN_UP_BOX);
			// Add edge threshold slider to the group
			m_EdgeThresholdSlider = new Fl_Value_Slider(20, 285, 200, 20, "Edge Threshold");
			m_EdgeThresholdSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_EdgeThresholdSlider->type(FL_HOR_NICE_SLIDER);
			m_EdgeThresholdSlider->labelfont(FL_COURIER);
			m_EdgeThresholdSlider->labelsize(12);
			m_EdgeThresholdSlider->minimum(0);
			m_EdgeThresholdSlider->maximum(500);
			m_EdgeThresholdSlider->step(1);
			m_EdgeThresholdSlider->value(m_eThreshold);
			m_EdgeThresholdSlider->align(FL_ALIGN_RIGHT);
			m_EdgeThresholdSlider->callback(cb_thresholdSlides);

			// Add do it button to the group
			m_DoItButton = new Fl_Button(330, 285, 50, 22, "&Do it");
			m_DoItButton->user_data((void*)(this));	// record self to be used by static callback functions
			m_DoItButton->callback(cb_do_it_button);
		edgeThresholdGroup->end();

		// Create a filter kernel interface
		Fl_Group* filterKernelGroup = new Fl_Group(10, 320, 380, 40);
			filterKernelGroup->box(FL_THIN_UP_BOX);
			// Add input text box to the group
			m_FilterKernelInput = new Fl_Input(60, 322, 110, 36, "Filter\nKernel");
			m_FilterKernelInput->value(m_FilterKernelText);
			m_FilterKernelInput->user_data((void*)(this));	// record self to be used by static callback functions
			m_FilterKernelInput->callback(cb_filterkernelinput);
			m_FilterKernelInputSize = new Fl_Input(205, 330, 25, 22, "Size");
			m_FilterKernelInputSize->value(m_FilterKernelSize);
			m_FilterKernelInputSize->user_data((void*)(this));	// record self to be used by static callback functions
			m_FilterKernelInputSize->callback(cb_filterkernelsize);

			// Add filter kernel normalize button to the group
			m_FilterKernelNormalizeButton = new Fl_Light_Button(240, 330, 80, 22, "Normalize");
			m_FilterKernelNormalizeButton->value(m_FilterKernelNormalize);
			m_FilterKernelNormalizeButton->user_data((void*)(this));	// record self to be used by static callback functions
			m_FilterKernelNormalizeButton->callback(cb_filterkernelnormalize);

			// Add filter kernel apply button to the group
			m_FilterKernelApplyButton = new Fl_Button(330, 330, 50, 22, "Apply");
			m_FilterKernelApplyButton->user_data((void*)(this));	// record self to be used by static callback functions
			m_FilterKernelApplyButton->callback(cb_filterkernelapply);
		filterKernelGroup->end();
    m_brushDialog->end();	

	// colors dialog definition
	m_colorsDialog = new Fl_Window(220, 225, "Color Selector");
		m_ColorChooser = new Fl_Color_Chooser(10, 20, 200, 195, "Color Blending");
		m_ColorChooser->user_data((void*)(this));	// record self to be used by static callback functions
		m_ColorChooser->rgb(m_nColorR, m_nColorG, m_nColorB);
		m_ColorChooser->callback(cb_colorChooser);
	m_colorsDialog->end();

	// paintly dialog definition
	m_paintlyDialog = new Fl_Window(400, 270, "Paintly Dialog");
		// Add a style choice to the dialog
		m_PaintlyStyleChoice = new Fl_Choice(50, 10, 120, 20, "&Style");
		m_PaintlyStyleChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_PaintlyStyleChoice->menu(paintlyStyleMenu);
		m_PaintlyStyleChoice->callback(cb_paintlyStyleChoice);

		// Add a stroke type choice to the dialog
		m_PaintlyStrokeTypeChoice = new Fl_Choice(220, 10, 110, 20, "S&troke");
		m_PaintlyStrokeTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_PaintlyStrokeTypeChoice->menu(paintlyStrokeTypeMenu);
		m_PaintlyStrokeTypeChoice->callback(cb_paintlyStrokeTypeChoice);
		m_PaintlyStrokeTypeChoice->deactivate();

		// Add run button to the dialog
		m_RunButton = new Fl_Button(340, 10, 40, 20, "&Run");
		m_RunButton->user_data((void*)(this));	// record self to be used by static callback functions
		m_RunButton->callback(cb_run_button);

		// Create a group that will hold the sliders for customized paintly
		paintlyCustomizeGroup = new Fl_Group(10, 35, 380, 230);
		paintlyCustomizeGroup->box(FL_THIN_UP_BOX);
			// Add threshold slider to the group
			m_PaintlyThresholdSlider = new Fl_Value_Slider(20, 40, 200, 20, "Threshold");
			m_PaintlyThresholdSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyThresholdSlider->type(FL_HOR_NICE_SLIDER);
			m_PaintlyThresholdSlider->labelfont(FL_COURIER);
			m_PaintlyThresholdSlider->labelsize(12);
			m_PaintlyThresholdSlider->minimum(0);
			m_PaintlyThresholdSlider->maximum(250);
			m_PaintlyThresholdSlider->step(1);
			m_PaintlyThresholdSlider->value(m_pThreshold);
			m_PaintlyThresholdSlider->align(FL_ALIGN_RIGHT);
			m_PaintlyThresholdSlider->callback(cb_paintlyThresholdSlides);

			// Add curvature slider to the group
			m_PaintlyCurvatureSlider = new Fl_Value_Slider(20, 65, 200, 20, "Curvature");
			m_PaintlyCurvatureSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyCurvatureSlider->type(FL_HOR_NICE_SLIDER);
			m_PaintlyCurvatureSlider->labelfont(FL_COURIER);
			m_PaintlyCurvatureSlider->labelsize(12);
			m_PaintlyCurvatureSlider->minimum(0.00);
			m_PaintlyCurvatureSlider->maximum(1.00);
			m_PaintlyCurvatureSlider->step(0.01);
			m_PaintlyCurvatureSlider->value(m_pCurvature);
			m_PaintlyCurvatureSlider->align(FL_ALIGN_RIGHT);
			m_PaintlyCurvatureSlider->callback(cb_paintlyCurvatureSlides);

			// Add blur slider to the group
			m_PaintlyBlurSlider = new Fl_Value_Slider(20, 90, 200, 20, "Blur");
			m_PaintlyBlurSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyBlurSlider->type(FL_HOR_NICE_SLIDER);
			m_PaintlyBlurSlider->labelfont(FL_COURIER);
			m_PaintlyBlurSlider->labelsize(12);
			m_PaintlyBlurSlider->minimum(0.00);
			m_PaintlyBlurSlider->maximum(1.00);
			m_PaintlyBlurSlider->step(0.01);
			m_PaintlyBlurSlider->value(m_pBlur);
			m_PaintlyBlurSlider->align(FL_ALIGN_RIGHT);
			m_PaintlyBlurSlider->callback(cb_paintlyBlurSlides);

			// Add grid size slider to the group
			m_PaintlyGridSizeSlider = new Fl_Value_Slider(20, 115, 200, 20, "Grid Size");
			m_PaintlyGridSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyGridSizeSlider->type(FL_HOR_NICE_SLIDER);
			m_PaintlyGridSizeSlider->labelfont(FL_COURIER);
			m_PaintlyGridSizeSlider->labelsize(12);
			m_PaintlyGridSizeSlider->minimum(0.00);
			m_PaintlyGridSizeSlider->maximum(1.00);
			m_PaintlyGridSizeSlider->step(0.01);
			m_PaintlyGridSizeSlider->value(m_pGridSize);
			m_PaintlyGridSizeSlider->align(FL_ALIGN_RIGHT);
			m_PaintlyGridSizeSlider->callback(cb_paintlyGridSizeSlides);

			// Add minStrokeL slider to the group
			m_PaintlyMinStrokeLSlider = new Fl_Value_Slider(20, 140, 200, 20, "MinStrokeL");
			m_PaintlyMinStrokeLSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyMinStrokeLSlider->type(FL_HOR_NICE_SLIDER);
			m_PaintlyMinStrokeLSlider->labelfont(FL_COURIER);
			m_PaintlyMinStrokeLSlider->labelsize(12);
			m_PaintlyMinStrokeLSlider->minimum(0);
			m_PaintlyMinStrokeLSlider->maximum(30);
			m_PaintlyMinStrokeLSlider->step(1);
			m_PaintlyMinStrokeLSlider->value(m_pMinStrokeL);
			m_PaintlyMinStrokeLSlider->align(FL_ALIGN_RIGHT);
			m_PaintlyMinStrokeLSlider->callback(cb_paintlyMinStrokeLSlides);

			// Add maxStrokeL slider to the group
			m_PaintlyMaxStrokeLSlider = new Fl_Value_Slider(20, 165, 200, 20, "MaxStrokeL");
			m_PaintlyMaxStrokeLSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyMaxStrokeLSlider->type(FL_HOR_NICE_SLIDER);
			m_PaintlyMaxStrokeLSlider->labelfont(FL_COURIER);
			m_PaintlyMaxStrokeLSlider->labelsize(12);
			m_PaintlyMaxStrokeLSlider->minimum(0);
			m_PaintlyMaxStrokeLSlider->maximum(30);
			m_PaintlyMaxStrokeLSlider->step(1);
			m_PaintlyMaxStrokeLSlider->value(m_pMaxStrokeL);
			m_PaintlyMaxStrokeLSlider->align(FL_ALIGN_RIGHT);
			m_PaintlyMaxStrokeLSlider->callback(cb_paintlyMaxStrokeLSlides);

			// Add alpha slider to the group
			m_PaintlyAlphaSlider = new Fl_Value_Slider(20, 190, 200, 20, "Alpha");
			m_PaintlyAlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyAlphaSlider->type(FL_HOR_NICE_SLIDER);
			m_PaintlyAlphaSlider->labelfont(FL_COURIER);
			m_PaintlyAlphaSlider->labelsize(12);
			m_PaintlyAlphaSlider->minimum(0.00);
			m_PaintlyAlphaSlider->maximum(1.00);
			m_PaintlyAlphaSlider->step(0.01);
			m_PaintlyAlphaSlider->value(m_pAlpha);
			m_PaintlyAlphaSlider->align(FL_ALIGN_RIGHT);
			m_PaintlyAlphaSlider->callback(cb_paintlyAlphaSlides);

			// Add layers slider to the group
			m_PaintlyLayersSlider = new Fl_Value_Slider(20, 215, 200, 20, "Layers");
			m_PaintlyLayersSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyLayersSlider->type(FL_HOR_NICE_SLIDER);
			m_PaintlyLayersSlider->labelfont(FL_COURIER);
			m_PaintlyLayersSlider->labelsize(12);
			m_PaintlyLayersSlider->minimum(1);
			m_PaintlyLayersSlider->maximum(5);
			m_PaintlyLayersSlider->step(1);
			m_PaintlyLayersSlider->value(m_pLayers);
			m_PaintlyLayersSlider->align(FL_ALIGN_RIGHT);
			m_PaintlyLayersSlider->callback(cb_paintlyLayersSlides);

			// Add R0 level slider to the group
			m_PaintlyR0LevelSlider = new Fl_Value_Slider(20, 240, 200, 20, "R0 Level");
			m_PaintlyR0LevelSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyR0LevelSlider->type(FL_HOR_NICE_SLIDER);
			m_PaintlyR0LevelSlider->labelfont(FL_COURIER);
			m_PaintlyR0LevelSlider->labelsize(12);
			m_PaintlyR0LevelSlider->minimum(0);
			m_PaintlyR0LevelSlider->maximum(5);
			m_PaintlyR0LevelSlider->step(1);
			m_PaintlyR0LevelSlider->value(m_pR0Level);
			m_PaintlyR0LevelSlider->align(FL_ALIGN_RIGHT);
			m_PaintlyR0LevelSlider->callback(cb_paintlyR0LevelSlides);

			// Add color sliders to the group
			m_PaintlyJrSlider = new Fl_Value_Slider(300, 40, 25, 80, "Jr");
			m_PaintlyJrSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyJrSlider->type(FL_VERT_NICE_SLIDER);
			m_PaintlyJrSlider->labelfont(FL_COURIER);
			m_PaintlyJrSlider->labelsize(12);
			m_PaintlyJrSlider->minimum(0.00);
			m_PaintlyJrSlider->maximum(1.00);
			m_PaintlyJrSlider->step(0.01);
			m_PaintlyJrSlider->value(m_pJr);
			m_PaintlyJrSlider->align(FL_ALIGN_BOTTOM);
			m_PaintlyJrSlider->callback(cb_paintlyJrSlides);

			m_PaintlyJgSlider = new Fl_Value_Slider(330, 40, 25, 80, "Jg");
			m_PaintlyJgSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyJgSlider->type(FL_VERT_NICE_SLIDER);
			m_PaintlyJgSlider->labelfont(FL_COURIER);
			m_PaintlyJgSlider->labelsize(12);
			m_PaintlyJgSlider->minimum(0.00);
			m_PaintlyJgSlider->maximum(1.00);
			m_PaintlyJgSlider->step(0.01);
			m_PaintlyJgSlider->value(m_pJg);
			m_PaintlyJgSlider->align(FL_ALIGN_BOTTOM);
			m_PaintlyJgSlider->callback(cb_paintlyJgSlides);

			m_PaintlyJbSlider = new Fl_Value_Slider(360, 40, 25, 80, "Jb");
			m_PaintlyJbSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyJbSlider->type(FL_VERT_NICE_SLIDER);
			m_PaintlyJbSlider->labelfont(FL_COURIER);
			m_PaintlyJbSlider->labelsize(12);
			m_PaintlyJbSlider->minimum(0.00);
			m_PaintlyJbSlider->maximum(1.00);
			m_PaintlyJbSlider->step(0.01);
			m_PaintlyJbSlider->value(m_pJb);
			m_PaintlyJbSlider->align(FL_ALIGN_BOTTOM);
			m_PaintlyJbSlider->callback(cb_paintlyJbSlides);

			m_PaintlyJhSlider = new Fl_Value_Slider(300, 150, 25, 80, "Jh");
			m_PaintlyJhSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyJhSlider->type(FL_VERT_NICE_SLIDER);
			m_PaintlyJhSlider->labelfont(FL_COURIER);
			m_PaintlyJhSlider->labelsize(12);
			m_PaintlyJhSlider->minimum(0.00);
			m_PaintlyJhSlider->maximum(1.00);
			m_PaintlyJhSlider->step(0.01);
			m_PaintlyJhSlider->value(m_pJh);
			m_PaintlyJhSlider->align(FL_ALIGN_BOTTOM);
			m_PaintlyJhSlider->callback(cb_paintlyJhSlides);

			m_PaintlyJsSlider = new Fl_Value_Slider(330, 150, 25, 80, "Js");
			m_PaintlyJsSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyJsSlider->type(FL_VERT_NICE_SLIDER);
			m_PaintlyJsSlider->labelfont(FL_COURIER);
			m_PaintlyJsSlider->labelsize(12);
			m_PaintlyJsSlider->minimum(0.00);
			m_PaintlyJsSlider->maximum(1.00);
			m_PaintlyJsSlider->step(0.01);
			m_PaintlyJsSlider->value(m_pJs);
			m_PaintlyJsSlider->align(FL_ALIGN_BOTTOM);
			m_PaintlyJsSlider->callback(cb_paintlyJsSlides);

			m_PaintlyJvSlider = new Fl_Value_Slider(360, 150, 25, 80, "Jv");
			m_PaintlyJvSlider->user_data((void*)(this));	// record self to be used by static callback functions
			m_PaintlyJvSlider->type(FL_VERT_NICE_SLIDER);
			m_PaintlyJvSlider->labelfont(FL_COURIER);
			m_PaintlyJvSlider->labelsize(12);
			m_PaintlyJvSlider->minimum(0.00);
			m_PaintlyJvSlider->maximum(1.00);
			m_PaintlyJvSlider->step(0.01);
			m_PaintlyJvSlider->value(m_pJv);
			m_PaintlyJvSlider->align(FL_ALIGN_BOTTOM);
			m_PaintlyJvSlider->callback(cb_paintlyJvSlides);
		paintlyCustomizeGroup->end();
		paintlyCustomizeGroup->deactivate();

	m_paintlyDialog->end();

}
