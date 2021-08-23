/*
 * CS559 Maze Project
 *
 * Class header file for the WorldWindow class. The WorldWindow is
 * the window in which the viewer's view of the world is displayed.
 *
 * (c) Stephen Chenney, University of Wisconsin at Madison, 2001-2002
 *
 */

/*
 *	SPECULATED GRADING: EVAN BRUNSWICK		|	POINTS				|
 *											|						|
 *	TEXTURING:								|						|
 *		- Wall.cpp							|	20					|
 *		- TicketBooth.cpp					|	 5					|
 *		- Merry.cpp							|	 5					|
 *											|						|
 *	PARAMETRIC INSTANCING:					|						|
 *		- Wall.cpp							|	20					|
 *		- HandRails.cpp						|	 5					|
 *		- Tree.cpp							|	 5					|
 * 											|						|
 *	SWEEP OBJECTS:							|						|
 *		- HandRails.cpp						|	25					|
 *		- Track.cpp							|	 5					|
 *											|						|
 *	CHANGE THE NAVIGATION SYSTEM			|						|
 *		- WorldWindow.cpp					|	20					|
 * -----------------------------------------|-----------------------|
 *	TOTAL									|  110					|
 */

#ifndef _WORLDWINDOW_H_
#define _WORLDWINDOW_H_

#include "Tree.h"
#include <Fl/Fl.h>
#include <Fl/Fl_Gl_Window.h>
#include "Ground.h"
#include "Track.h"
#include "Wall.h"
#include "Road.h"
#include "HandRails.h"
#include "TicketBooth.h"
#include <string>
#include "Merry.h"


// Subclass the Fl_Gl_Window because we want to draw OpenGL in here.
class WorldWindow : public Fl_Gl_Window {

public:
	// Constructor takes window position and dimensions, the title.
	WorldWindow(int x, int y, int w, int h, char *label);
	~WorldWindow();
	// draw() method invoked whenever the view changes or the window
	// otherwise needs to be redrawn.
	void	draw(void);

	// Event handling method. Uses only mouse events.
	int	handle(int);

	// Update the world according to any events that have happened since
	// the last time this method was called.
	bool	Update(float);



private:
	Ground	    ground;	    // The ground object.
	Track  traintrack;	    // The train and track.

	// user implemented methods
	Road		road;				// The roadway which uses asphalt.tga texturing. needs work
	Road*		path;
	Merry		merry;
	Road*		roller_coaster_base;
	TicketBooth ticketBooth;
	HandRails*	test;				// Handrails which are parametrically instanced. Could also be sweep objects depending on how the teach considers them.
	HandRails*	sideRails[2];		// just another instance of Handrails. astetical only.
	Wall*		wall[5];			// Parametrically instanced and textured walls.

	// Tree crap.
	Tree*		tree_array[33];		// Parametrically instanced trees. Final parametric object allowed.




	static const double FOV_X; // The horizontal field of view.

	float	phi;	// Viewer's inclination angle.
	float	theta;	// Viewer's azimuthal angle.
	float	dist;	// Viewer's distance from the look-at point.
	float	x_at;	// The x-coord to look at.
	float	y_at;	// The y-coord to look at. z_at is assumed 2.0.

	int	view;		// defines where we are looking at.

	int     button;	// The mouse button that is down, -1 if none.
	int	x_last;	// The location of the most recent mouse event
	int	y_last;
	int	x_down; // The location of the mouse when the button was pushed
	int	y_down;
	float   phi_down;   // The view inclination angle when the mouse
			    // button was pushed
	float   theta_down; // The view azimuthal angle when the mouse
			    // button was pushed
	float	dist_down;  // The distance when the mouse button is pushed.
	float	x_at_down;  // The x-coord to look at when the mouse went down.
	float	y_at_down;  // The y-coord to look at when the mouse went down.

	void	Drag(float);	// The function to call for mouse drag events
	void	Initialize_Walls(void);
	void	Look_at_location(int option);	// will pass it a int and it will look at a certain object for us.

};


#endif
