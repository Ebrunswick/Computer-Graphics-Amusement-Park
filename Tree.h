/*
 * Tree.h: Header file for a class that draws the ground.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#ifndef _TREE_H_
#define _TREE_H_

#include <include/GL/glew.h>
#include <Fl/gl.h>


class Tree {
private:
    GLubyte         display_list;   // The display list that does all the work.
    GLuint          texture_obj;    // The object for the grass texture.
    bool            initialized;    // Whether or not we have been initialised.
    float           height;
    float           radius;
    float           x_coordinate;
    float           y_coordinate;
    float           z_coordinate;

public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Tree(void) { display_list = 0; initialized = false; height = 3.0f; radius = 1.0f; x_coordinate = y_coordinate = z_coordinate = 0; };
    Tree(float f_height, float f_radius, float x, float y, float z);


    // Destructor. Frees the display lists and texture object.
    ~Tree(void);

    // Initializer. Creates the display list.
    bool    Initialize(void);

    // Does the drawing.
    void    Draw(void);
};


#endif