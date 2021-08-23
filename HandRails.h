/*
 * HandRails.h: Header file for a class that draws stright hand rails.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#ifndef _HANDRAILS_H_
#define _HANDRAILS_H_

#include <Fl/gl.h>

class HandRails {
private:
    GLubyte display_list;   // The display list that does all the work.
    GLuint  texture_obj;    // The object for the grass texture.
    bool    initialized;    // Whether or not we have been initialised.

    // object parameters
    float radius;
    float height;
    float length;
    float spacing; // empty space between veritcal rails.

    float   x_coordinate, y_coordinate, z_coordinate;


public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    HandRails(void) { display_list = 0; initialized = false; };
    HandRails(float radius, float height, float length, float spacing) { this->radius = radius; this->height = height; this->length = length; this->spacing = spacing; }

    // Destructor. Frees the display lists and texture object.
    ~HandRails(void);

    // Initializer. Creates the display list.
    bool    Initialize(void);

    // Does the drawing.
    void    Draw(void);
    void    SetCoordinates(float x, float y, float z) { x_coordinate = x; y_coordinate = y; z_coordinate = z; }

};


#endif
