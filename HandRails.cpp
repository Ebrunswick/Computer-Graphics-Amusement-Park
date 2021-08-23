

#include "HandRails.h"
#include <FL/math.h>
#include <gl/GLU.h>

HandRails::
~HandRails() {

    if (initialized) {
        glDeleteLists(display_list, 1);
        glDeleteTextures(1, &texture_obj);
    }
}

bool HandRails::
Initialize() {

    GLUquadric* quadratic_obj = gluNewQuadric();

    gluQuadricNormals(quadratic_obj, GLU_SMOOTH);
    display_list =  glGenLists(1);
    glNewList(display_list, GL_COMPILE);
    int count = 0;

    glColor3f(0.6f, 0.6f, 0.6f);
    for (int i = 0; i < length; i += spacing) {
        gluCylinder(quadratic_obj, radius, radius, height, 10, 32);
        glTranslatef(0, spacing - (radius*2), 0); // need to test the spacing
        count++;
    }

    gluCylinder(quadratic_obj, radius, radius, height, 10, 32);
    // these rotates are affecting the object defined below it
    glTranslatef(0, radius, height);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);


    glColor3f(0.6f, 0.6f, 0.6f);
    gluCylinder(quadratic_obj, radius, radius, length - (radius * 2 * (count-1)), 10, 32);
    glTranslatef(0, 0, (height/2));
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    
    glEndList();

    initialized = true;
    return true;
}

void HandRails::
Draw() {
    glPushMatrix();
    glTranslatef(x_coordinate, y_coordinate, z_coordinate);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glCallList(display_list);
    glPopMatrix();
}