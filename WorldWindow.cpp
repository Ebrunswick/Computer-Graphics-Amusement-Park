/*
 * CS559 Maze Project
 *
 * Class file for the WorldWindow class.
 *
 * (c) Stephen Chenney, University of Wisconsin at Madison, 2001-2002
 *
 */

#include "WorldWindow.h"
#include <Fl/math.h>
#include <Fl/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <FL/glut.H>
#include <iostream>

const double WorldWindow::FOV_X = 45.0;

WorldWindow::WorldWindow(int x, int y, int width, int height, char *label)
	: Fl_Gl_Window(x, y, width, height, label)
{
    button = -1;

    // Initial viewing parameters.
    phi = 45.0f;
    theta = 0.0f;
    dist = 100.0f;
    x_at = 0.0f;
    y_at = 0.0f;
	view = 0;
	
	srand(time(NULL));
	int height_rand;
	int x_rand;
	int y_rand;
	float r_rand;
	// user added stuff
	for (int i = 0; i < 33; i++) {
		height_rand = rand() % 10 + 1;
		x_rand = rand() % 11 - 5; // rand from -5 to 5
		y_rand = rand() % 11 - 5; // rand from -5 to 5
		r_rand = rand() % 11 / 10; // rand of 0 to 1
		tree_array[i] = new Tree(10 + height_rand, 0.5f + r_rand, 43 - 2.5*i + x_rand, -40 + y_rand, 0.0f);
	}

	// Handrails/guiders thingys
	test = new HandRails(0.125, 2, 24, 3);
	sideRails[0] = new HandRails(0.125, 2, 24, 3);
	sideRails[1] = new HandRails(0.125, 2, 24, 3);

	// Road/path work
	path = new Road(20, 10, 30, 0, 0.125);
	roller_coaster_base = new Road(20, 20, 0, 0, 0.0125);


	// West, North, East, SouthWest, SouthEast
	wall[0] = new Wall(46, 2, 10);
	wall[1] = new Wall(2, 50, 10);
	wall[2] = new Wall(46, 2, 10);
	wall[3] = new Wall(2, 20, 10);
	wall[4] = new Wall(2, 20, 10);
}


void
WorldWindow::draw(void)
{
    double  eye[3];
    float   color[4], dir[4];

    if ( ! valid() )
    {
		// Stuff in here doesn't change from frame to frame, and does not
		// rely on any coordinate system. It only has to be done if the
		// GL context is damaged.

		double	fov_y;

		// Sets the clear color to sky blue.
		glClearColor(0.53f, 0.81f, 0.92f, 1.0);

		// Turn on depth testing
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Turn on back face culling. Faces with normals away from the viewer
		// will not be drawn.
		glEnable(GL_CULL_FACE);

		// Enable lighting with one light.
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

		// Ambient and diffuse lighting track the current color.
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);

		// Turn on normal vector normalization. You don't have to give unit
		// normal vector, and you can scale objects.
		glEnable(GL_NORMALIZE);

		// Set up the viewport.
		glViewport(0, 0, w(), h());

		// Set up the persepctive transformation.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		fov_y = 360.0f / M_PI * atan(h() * tan(FOV_X * M_PI / 360.0) / w());
		gluPerspective(fov_y, w() / (float)h(), 1.0, 1000.0);

		// Do some light stuff. Diffuse color, and zero specular color
		// turns off specular lighting.
		color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f; color[3] = 1.0f;
		glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
		color[0] = 0.0f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 1.0f;
		glLightfv(GL_LIGHT0, GL_SPECULAR, color);

		// Initialize all the objects.
		ground.Initialize();
		traintrack.Initialize();
		ticketBooth.Initialize();
		merry.Initialize();
		path->Initialize();
		roller_coaster_base->Initialize();

		// Handrails initialize
		test->Initialize();
		test->SetCoordinates(50, 0, 0);
		sideRails[0]->Initialize();
		sideRails[1]->Initialize();
		sideRails[0]->SetCoordinates(46, -10, 0);
		sideRails[1]->SetCoordinates(46, 10, 0);

		this->Initialize_Walls();

		for (int i = 0; i < 33; ++i) {
			tree_array[i]->Initialize();
		}
    }

    // Stuff out here relies on a coordinate system or must be done on every
    // frame.

    // Clear the screen. Color and depth.
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Set up the viewing transformation. The viewer is at a distance
    // dist from (x_at, y_ay, 2.0) in the direction (theta, phi) defined
    // by two angles. They are looking at (x_at, y_ay, 2.0) and z is up.

	/*
	 * This is all the camera work. yes it looks janky, yes it is functional
	 * I would fix this and make it look much nicer if I had more time to properly
	 * design this section.
	 */


	if (view == 1) {				// this is the ticket booth view
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(40, -5, 3, -40, -5, 3, 0.0, 0.0, 1.0);
	}
	else if (view == 2) { // i'll make this into a somewhat nice view
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(40, -25, 3, -40, -50, 3, 0.0, 0.0, 1.0);
	}
	else if (view == 3) { // this will be the roller coaster view
		float cam_angle[3] = {0.0f, 0.0f, 1.0f};
		float look_at[3];
		float track_pos[3];
		float tangent[3];

		traintrack.Evaluate_Position(track_pos, tangent); // tangent comes back normalized.

		cam_angle[0] = (-tangent[0] * tangent[2]);
		cam_angle[1] = (-tangent[1] * tangent[2]);
		cam_angle[2] = (tangent[1] * tangent[1]) + (tangent[0] * tangent[0]);
		// good enough for student project work imo.
		eye[0] = track_pos[0] + cam_angle[0]* 2;	look_at[0] = 100 * tangent[0];	
		eye[1] = track_pos[1] + cam_angle[1]* 2;	look_at[1] = 100 * tangent[1];
		eye[2] = track_pos[2] + cam_angle[2] * 2;	look_at[2] = 100 * tangent[2];
/*
		if (track_pos[0] >= 0 && track_pos[1] >= 0) {
			eye[0] += 0.5;
			eye[1] += 0.5;
		}
		else if (track_pos[0] < 0 && track_pos[1] >= 0) {
			eye[0] += 0.5;
			eye[1] -= 0.5;
		}
		else if (track_pos[0] < 0 && track_pos[1] < 0) {
			eye[0] -= 0.5;
			eye[1] -= 0.5;
		}
		else {
			eye[0] -= 0.5;
			eye[1] += 0.5;
		}
*/

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(	eye[0],			eye[1],			eye[2] + 2.0f,
					look_at[0],		look_at[1],		look_at[2],
					cam_angle[0],	cam_angle[1],	cam_angle[2]);
	}
	else if (view == 4) { // i'll make this into a somewhat nice view
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(120, 20, 50, 0, 0, 0, 0.0, 0.0, 1.0);
	}
	else if (view == 5) { // Merry-go-round view. except the merry no go round
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(-10, 15, 5, -50, 45, 3, 0.0, 0.0, 1.0);
	}
	else {
		eye[0] = x_at + dist * cos(theta * M_PI / 180.0) * cos(phi * M_PI / 180.0);
		eye[1] = y_at + dist * sin(theta * M_PI / 180.0) * cos(phi * M_PI / 180.0);
		eye[2] = 2.0 + dist * sin(phi * M_PI / 180.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		// maybe something here for the eye?
		gluLookAt(eye[0], eye[1], eye[2], x_at, y_at, 2.0, 0.0, 0.0, 1.0);
	}


    // Position the light source. This has to happen after the viewing
    // transformation is set up, so that the light stays fixed in world
    // space. This is a directional light - note the 0 in the w component.
    dir[0] = 1.0; dir[1] = 1.0; dir[2] = 1.0; dir[3] = 0.0;
    glLightfv(GL_LIGHT0, GL_POSITION, dir);

    // Draw stuff. Everything.
    ground.Draw();
	path->Draw();
	roller_coaster_base->Draw();
	merry.Draw();
	ticketBooth.Draw();
    traintrack.Draw();
	test->Draw();
	sideRails[0]->Draw();
	sideRails[1]->Draw();

	for (int i = 0; i < 5; ++i) {
		wall[i]->Draw();
	}


	for (int i = 0; i < 33; ++i) {
		tree_array[i]->Draw();
	}
}


void
WorldWindow::Drag(float dt)
{
    int	    dx = x_down - x_last;
    int     dy = y_down - y_last;

    switch ( button )
    {
      case FL_LEFT_MOUSE:
	// Left button changes the direction the viewer is looking from.
	theta = theta_down + 360.0f * dx / (float)w();
	while ( theta >= 360.0f )
	    theta -= 360.0f;
	while ( theta < 0.0f )
	    theta += 360.0f;
	phi = phi_down + 90.0f * dy / (float)h();
	if ( phi > 89.0f )
	    phi = 89.0f;
	if ( phi < -5.0f )
	    phi = -5.0f;
	break;
      case FL_MIDDLE_MOUSE:
	// Middle button moves the viewer in or out.
	dist = dist_down - ( 0.5f * dist_down * dy / (float)h() );
	if ( dist < 1.0f )
	    dist = 1.0f;
	break;
      case FL_RIGHT_MOUSE: {
	// Right mouse button moves the look-at point around, so the world
	// appears to move under the viewer.
	float	x_axis[2];
	float	y_axis[2];

	x_axis[0] = -(float)sin(theta * M_PI / 180.0);
	x_axis[1] = (float)cos(theta * M_PI / 180.0);
	y_axis[0] = x_axis[1];
	y_axis[1] = -x_axis[0];

	x_at = x_at_down + 100.0f * ( x_axis[0] * dx / (float)w()
				    + y_axis[0] * dy / (float)h() );
	y_at = y_at_down + 100.0f * ( x_axis[1] * dx / (float)w()
				    + y_axis[1] * dy / (float)h() );
	} break;
      default:;
    }
}


bool
WorldWindow::Update(float dt)
{
    // Update the view. This gets called once per frame before doing the
    // drawing.

    if ( button != -1 ) // Only do anything if the mouse button is down.
	Drag(dt);

    // Animate the train.
    traintrack.Update(dt);

    return true;
}


int
WorldWindow::handle(int event)
{
    // Event handling routine. Only looks at mouse events.
    // Stores a bunch of values when the mouse goes down and keeps track
    // of where the mouse is and what mouse button is down, if any.
    switch ( event )
    {
      case FL_PUSH:
			button = Fl::event_button();
			x_last = x_down = Fl::event_x();
			y_last = y_down = Fl::event_y();
			phi_down = phi;
			theta_down = theta;
			dist_down = dist;
			x_at_down = x_at;
			y_at_down = y_at;
			return 1;
      case FL_DRAG:
			x_last = Fl::event_x();
			y_last = Fl::event_y();
			return 1;
      case FL_RELEASE:
	        button = -1;
			return 1;

	  case FL_KEYBOARD:
			this->Look_at_location(Fl::event_key()); // send the event key to the system to go to specific view
			return 1;
    }

    // Pass any other event types on the superclass.
    return Fl_Gl_Window::handle(event);
}



void WorldWindow::Look_at_location(int key) {

	switch (key) {
	case 'b':		// b for Booth
		view ^= 1; // toggle a not equals.
		break;
	case 'f':		// forrest
		view ^= 2;
		break;

	case 'r':		// roller coaster.
		view ^= 3;
		break;	
	
	case 'w':		// walls
		view ^= 4;
		break;

	case 'm':		// Merry - go - round
		view ^= 5;
		break;
	}

}



void
WorldWindow::Initialize_Walls() {
	for (int i = 0; i < 5; ++i) {
		wall[i]->Initialize();
	}

	wall[0]->SetCoordinates(0, -48, 0);
	wall[1]->SetCoordinates(-48, 0, 0);
	wall[2]->SetCoordinates(0, 48, 0);
	wall[3]->SetCoordinates(48, -30, 0);
	wall[4]->SetCoordinates(48, 30, 0);
}

WorldWindow::~WorldWindow() {
	// delete the memory for the walls.
	for (int i = 0; i < 5; i++) {
		delete wall[i];
	}

	// delete the memory for the trees.
	for (int i = 0; i < 33; i++) {
		delete tree_array[i];
	}

	// delete the road object
	delete path;
	delete roller_coaster_base;
	delete test;
	delete[]sideRails;

}