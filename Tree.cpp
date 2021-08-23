/*
 * Tree.cpp: A class for drawing the Tree.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#include "Tree.h"
#include "libtarga.h"
#include <stdio.h>
#include <gl/glut.h>
#include <GL/GLU.h>




Tree::Tree(float f_height, float f_radius, float x, float y, float z) { 
    display_list =      0; 
    initialized =       false;
    // tree aspects
    height =            f_height; 
    radius =            f_radius;
    // coordinates
    x_coordinate =      x;
    y_coordinate =      y;
    z_coordinate =      z;
}

 // Destructor
Tree::~Tree(void)
{
    if (initialized)
    {
        glDeleteLists(display_list, 1);
        glDeleteTextures(1, &texture_obj);
    }
}


// Initializer. Returns false if something went wrong, like not being able to
// load the texture.
bool
Tree::Initialize(void)
{
    GLUquadric * quadratic_obj = gluNewQuadric();

    gluQuadricNormals(quadratic_obj, GLU_SMOOTH);

    display_list = glGenLists(1);
    glNewList(display_list, GL_COMPILE);

    // example brown color. hoping to texture map it later.
    glColor3f(0.5f, 0.35f, 0.05f);

    //gluQuadricTexture(GLUquadricObj * qobj, GLboolean textureCoords);
//  Note: The cylinder is not closed at the top or bottom.The disks at the base and at the top are not drawn.
    gluCylinder(quadratic_obj, radius, radius, height/3.0, 10, 16);
    glTranslatef(0, 0, height / 3);
    // now for the green cone object which is the "leaves"

    glColor3f(0.0f, 4.0f, 0.0f);
    gluCylinder(quadratic_obj, radius * 2, 0, (height/3 * 2), 10, 16);
    glTranslatef(0, 0, height); // might need to check this for positioning

    glEndList();

    // We only do all this stuff once, when the GL context is first set up.
    initialized = true;

    return true;
}


// Draw just calls the display list we set up earlier.
void
Tree::Draw(void)
{
    glPushMatrix();
    glTranslatef(x_coordinate, y_coordinate, z_coordinate);
    glCallList(display_list);
    glPopMatrix();
}


