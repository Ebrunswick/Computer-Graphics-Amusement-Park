/*
 * Merry.h: Header file for a class that draws the Merry-go-round.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#ifndef _Merry_H_
#define _Merry_H_

#include <Fl/gl.h>

class Merry {
private:
    GLubyte     display_list;   // The display list that does all the work.
    GLuint      texture_obj;    // Need an texture for this.
    bool        initialized;    // Whether or not we have been initialised.

    // Custom Defined Members
    GLdouble    base_radius;
    GLdouble    column_radius;
    float       x_position;
    float       y_position;
    float       z_position;

public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Merry(void) { display_list = 0; initialized = false;};

    // Destructor. Frees the display lists and texture object.
    ~Merry(void);

    // Initializer. Creates the display list.
    bool    Initialize(void);

    // Does the drawing.
    void    Draw(void);
    void    SetCoordinates(float x, float y, float z) { x_position = x; y_position = y; z_position = z; }
};


#endif
