/*
 * Wall.cpp: A class for drawing a wall around the sandbox.
 *
 * Edited by: Evan Brunswick
 * Date Created: 2/24/21
 * Date Edited:  2/24/21
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#include "Wall.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

 // Destructor
Wall::~Wall(void)
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
Wall::Initialize(void)
{
    ubyte* image_data;
    int	    image_height, image_width;

    // Load the image for the texture. The texture file has to be in
    // a place where it will be found.
    if (!(image_data = (ubyte*)tga_load("stone-wall.tga", &image_width,
        &image_height, TGA_TRUECOLOR_24)))
    {
        fprintf(stderr, "Wall::Initialize: Couldn't load stone-wall.tga\n");
        return false;
    }

    glGenTextures(1, &texture_obj);
    glBindTexture(GL_TEXTURE_2D, texture_obj);

    // This sets a parameter for how the texture is loaded and interpreted.
    // basically, it says that the data is packed tightly in the image array.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // This sets up the texture with high quality filtering. First it builds
    // mipmaps from the image data, then it sets the filtering parameters
    // and the wrapping parameters. We want the grass to be repeated over the
    // ground.
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image_width, image_height,
        GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_NEAREST_MIPMAP_LINEAR);

    // This says what to do with the texture. Modulate will multiply the
    // texture by the underlying color.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


    display_list = glGenLists(1);
    glNewList(display_list, GL_COMPILE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_obj);

    glColor3f(1.0f, 1.0f, 1.0f);

    this->Initialize_Object(wall_length, wall_width, wall_height);

    glDisable(GL_TEXTURE_2D);
    glEndList();
   
    initialized = true;
    return true;
}


// Draw just calls the display list we set up earlier.
void
Wall::Draw(void)
{
    glPushMatrix();
    glTranslatef(x_coordinate, y_coordinate, z_coordinate);
    glCallList(display_list);
    glPopMatrix();
}

void Wall::Initialize_Object(float length, float width, float height) {
    glBegin(GL_QUADS);
    // front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0, 1);
    glVertex3f(length, width, height);
    glTexCoord2f(0, 0);
    glVertex3f(-length, width, height);
    glTexCoord2f(1, 0);
    glVertex3f(-length, -width, height);
    glTexCoord2f(1, 1);
    glVertex3f(length, -width, height);

    // Bottom?
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1, 1);
    glVertex3f(length, -width, 0.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-length, -width, 0.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-length, width, 0.0f);
    glTexCoord2f(1, 0);
    glVertex3f(length, width, 0.0f);

    // something, think right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 1);
    glVertex3f(length, width, 0.0f);
    glTexCoord2f(0, 0);
    glVertex3f(length, width, height);
    glTexCoord2f(1, 0);
    glVertex3f(length, -width, height);
    glTexCoord2f(1, 1);
    glVertex3f(length, -width, 0.0f);

    // something, think left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0, 0);
    glVertex3f(-length, width, height);
    glTexCoord2f(1, 0);
    glVertex3f(-length, width, 0.0f);
    glTexCoord2f(1, 1);
    glVertex3f(-length, -width, 0.0f);
    glTexCoord2f(0, 1);
    glVertex3f(-length, -width, height);


    // something, think front
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0, 1);
    glVertex3f(length, width, height);
    glTexCoord2f(0, 0);
    glVertex3f(length, width, 0.0f);
    glTexCoord2f(1, 0);
    glVertex3f(-length, width, 0.0f);
    glTexCoord2f(1, 1);
    glVertex3f(-length, width, height);

    // back or bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0, 1);
    glVertex3f(length, -width, 0.0f);
    glTexCoord2f(0, 0);
    glVertex3f(length, -width, height);
    glTexCoord2f(1, 0);
    glVertex3f(-length, -width, height);
    glTexCoord2f(1, 1);
    glVertex3f(-length, -width, 0.0f);

    glEnd();
}


