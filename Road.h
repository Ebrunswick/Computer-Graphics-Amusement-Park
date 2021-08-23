/*
 * Road.h: Header file for a class that draws the road on the ground.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#ifndef _ROAD_H_
#define _ROAD_H_

#include <Fl/gl.h>

class Road {
private:
    GLubyte     display_list;   // The display list that does all the work.
    GLuint      texture_obj;    // Need an texture for this.
    bool        initialized;    // Whether or not we have been initialised.

    // Custom Defined Members
    GLdouble    path_length;
    GLdouble    path_width;
    float       x_position;
    float       y_position;
    float       z_position;

public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Road(void) { display_list = 0; initialized = false; path_length = path_width = 1; x_position = y_position = z_position = 0.0f; };
    Road(GLdouble specified_path_length, GLdouble specified_path_width, float x, float y, float z);

    // Destructor. Frees the display lists and texture object.
    ~Road(void);

    // Initializer. Creates the display list.
    bool    Initialize(void);

    // Does the drawing.
    void    Draw(void);
    void    SetCoordinates(float x, float y, float z) { x_position = x; y_position = y; z_position = z; }
};


#endif
