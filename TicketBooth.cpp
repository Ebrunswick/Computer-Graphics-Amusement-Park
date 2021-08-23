/*	Author:			Evan Brunswick
 *	Filename:		TicketBooth.cpp
 *	Created Date:	03/08/2021
 *
 *	Just a bare minimum simple ticket booth to get points for texture implememntation.
 */

#include "TicketBooth.h"
#include "libtarga.h"
#include <stdio.h>
#include <gl/GLU.h>

TicketBooth::TicketBooth(void) {
	display_list = 0;
	initialized = false;
}

TicketBooth:: ~TicketBooth(void) {
	if (initialized) {
		glDeleteLists(display_list, 1);
		glDeleteTextures(1, &texture_obj);
	}
}

bool TicketBooth::Initialize(void) {
	ubyte* image_data;
	int	    image_height, image_width;


	if (!(image_data = (ubyte*)tga_load("wood.tga", &image_width,
		&image_height, TGA_TRUECOLOR_24)))
	{
		fprintf(stderr, "Ground::Initialize: Couldn't load grass.tga\n");
		return false;
	}


	glGenTextures(1, &texture_obj);
	glBindTexture(GL_TEXTURE_2D, texture_obj);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image_width, image_height, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Begin student work
	display_list = glGenLists(1);
	glNewList(display_list, GL_COMPILE);
	// Use white, because the texture supplies the color.
	glColor3f(1.0, 1.0, 1.0);

	// Turn on texturing and bind the grass texture.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_obj);

	// Base 
	glBegin(GL_QUADS);
		//  base top
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0, 1);		glVertex3f(1, 1, 1);
		glTexCoord2f(0, 0);		glVertex3f(-1, 1, 1);
		glTexCoord2f(1, 0);		glVertex3f(-1, -1, 1);
		glTexCoord2f(1, 1);		glVertex3f(1, -1, 1);

		// base bottom
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(1, 1);		glVertex3f(1, -1, 0);
		glTexCoord2f(0, 1);		glVertex3f(-1, -1, 0);
		glTexCoord2f(0, 0);		glVertex3f(-1, 1, 0);
		glTexCoord2f(1, 0);		glVertex3f(1, 1, 0);

		// base right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 1);		glVertex3f(1, 1, 0);
		glTexCoord2f(0, 0);		glVertex3f(1, 1, 1);
		glTexCoord2f(1, 0);		glVertex3f(1, -1, 1);
		glTexCoord2f(1, 1);		glVertex3f(1, -1, 0);

		// base left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 1);		glVertex3f(-1, 1, 1);
		glTexCoord2f(0, 0);		glVertex3f(-1, 1, 0);
		glTexCoord2f(1, 0);		glVertex3f(-1, -1, 0);
		glTexCoord2f(1, 1);		glVertex3f(-1, -1, 1);

		// base front
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0, 1);		glVertex3f(1, 1, 1);
		glTexCoord2f(0, 0);		glVertex3f(1, 1, 0);
		glTexCoord2f(1, 0);		glVertex3f(-1, 1, 0);
		glTexCoord2f(1, 1);		glVertex3f(-1, 1, 1);

		// base rear
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0, 1);		glVertex3f(1, -1, 0);
		glTexCoord2f(0, 0);		glVertex3f(1, -1, 1);
		glTexCoord2f(1, 0);		glVertex3f(-1, -1, 1);
		glTexCoord2f(1, 1);		glVertex3f(-1, -1, 0);
	glEnd();

	// pole - left adjusted.
	glBegin(GL_QUADS);
		// base front
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1, 1);		glVertex3f(1, -0.75, 2);
		glTexCoord2f(1, 0);		glVertex3f(1, -0.75, 1.001f);
		glTexCoord2f(0, 0);		glVertex3f(-1, -0.75, 1.001f);
		glTexCoord2f(0, 1);		glVertex3f(-1, -0.75, 2);

		// base rear(left somehow)
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1, 1);		glVertex3f(1, -1, 1.001f);
		glTexCoord2f(1, 0);		glVertex3f(1, -1, 2);
		glTexCoord2f(0, 0);		glVertex3f(-1, -1, 2);
		glTexCoord2f(0, 1);		glVertex3f(-1, -1, 1.001f);

		// base left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1, 1);		glVertex3f(1, -1, 2);
		glTexCoord2f(1, 0);		glVertex3f(1, -1, 1.001f);
		glTexCoord2f(0, 0);		glVertex3f(1, -0.75, 1.001f);
		glTexCoord2f(0, 1);		glVertex3f(1, -0.75, 2);

		// base right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1, 1);		glVertex3f(-1, -1, 1.001f);
		glTexCoord2f(1, 0);		glVertex3f(-1, -1, 2);
		glTexCoord2f(0, 0);		glVertex3f(-1, -0.75, 2);
		glTexCoord2f(0, 1);		glVertex3f(-1, -0.75, 1.001f);

		//  base top
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(1, 1);		glVertex3f(-1, -1, 2);
		glTexCoord2f(1, 0);		glVertex3f(1, -1, 2);
		glTexCoord2f(0, 0);		glVertex3f(1, -0.75, 2);
		glTexCoord2f(0, 1);		glVertex3f(-1, -0.75, 2);

		// base bottom
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(1, 0);		glVertex3f(-1, -0.75, 1.001f);
		glTexCoord2f(0, 0);		glVertex3f(1, -0.75, 1.001f);
		glTexCoord2f(0, 1);		glVertex3f(1, -1, 1.001f);
		glTexCoord2f(1, 1);		glVertex3f(-1, -1, 1.001f);
	glEnd();

	// pole right
	glBegin(GL_QUADS);
	//  base top
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0, 1);		glVertex3f(-1, 0.75, 1.999f);
		glTexCoord2f(0, 0);		glVertex3f(1, 0.75, 1.999f);
		glTexCoord2f(1, 0);		glVertex3f(1, 1, 1.999f);
		glTexCoord2f(1, 1);		glVertex3f(-1, 1, 1.999f);

		// base bottom
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(1, 1);		glVertex3f(-1, 1, 1.001f);
		glTexCoord2f(0, 1);		glVertex3f(1, 1, 1.001f);
		glTexCoord2f(0, 0);		glVertex3f(1, 0.75, 1.001f);
		glTexCoord2f(1, 0);		glVertex3f(-1, 0.75, 1.001f);

		// base right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 1);		glVertex3f(-1, 0.75, 1.001f);
		glTexCoord2f(0, 0);		glVertex3f(-1, 0.75, 1.999f);
		glTexCoord2f(1, 0);		glVertex3f(-1, 1, 1.999f);
		glTexCoord2f(1, 1);		glVertex3f(-1, 1, 1.001f);

		// base left
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 1);		glVertex3f(1, 0.75, 1.999f);
		glTexCoord2f(0, 0);		glVertex3f(1, 0.75, 1.001f);
		glTexCoord2f(1, 0);		glVertex3f(1, 1, 1.001f);
		glTexCoord2f(1, 1);		glVertex3f(1, 1, 1.999f);

		// base front
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0, 1);		glVertex3f(-1, 0.75, 1.999f);
		glTexCoord2f(0, 0);		glVertex3f(-1, 0.75, 1.001f);
		glTexCoord2f(1, 0);		glVertex3f(1, 0.75, 1.001f);
		glTexCoord2f(1, 1);		glVertex3f(1, 0.75, 1.999f);

		// base rear
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0, 1);		glVertex3f(-1, 1, 1.001f);
		glTexCoord2f(0, 0);		glVertex3f(-1, 1, 1.999f);
		glTexCoord2f(1, 0);		glVertex3f(1, 1, 1.999f);
		glTexCoord2f(1, 1);		glVertex3f(1, 1, 1.001f);
	glEnd();

	// The back of the ticketBooth
	glBegin(GL_QUADS);
	//  base top
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 1);		glVertex3f(-0.75, 0.75, 2);
	glTexCoord2f(0, 0);		glVertex3f(-1, 0.75, 2);
	glTexCoord2f(1, 0);		glVertex3f(-1, -0.75, 2);
	glTexCoord2f(1, 1);		glVertex3f(-0.75, -0.75, 2);

	// base bottom
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1, 1);		glVertex3f(-0.75, -0.75, 1);
	glTexCoord2f(0, 1);		glVertex3f(-1, -0.75, 1);
	glTexCoord2f(0, 0);		glVertex3f(-1, 0.75, 1);
	glTexCoord2f(1, 0);		glVertex3f(-0.75, 0.75, 1);

	// base right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 1);		glVertex3f(-0.75, 0.75, 1);
	glTexCoord2f(0, 0);		glVertex3f(-0.75, 0.75, 2);
	glTexCoord2f(1, 0);		glVertex3f(-0.75, -0.75, 2);
	glTexCoord2f(1, 1);		glVertex3f(-0.75, -0.75, 1);

	// base left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 1);		glVertex3f(-1, 0.75, 2);
	glTexCoord2f(0, 0);		glVertex3f(-1, 0.75, 1);
	glTexCoord2f(1, 0);		glVertex3f(-1, -0.75, 1);
	glTexCoord2f(1, 1);		glVertex3f(-1, -0.75, 2);

	// base front
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 1);		glVertex3f(-0.75, 0.75, 2);
	glTexCoord2f(0, 0);		glVertex3f(-0.75, 0.75, 1);
	glTexCoord2f(1, 0);		glVertex3f(-1, 0.75, 1);
	glTexCoord2f(1, 1);		glVertex3f(-1, 0.75, 2);

	// base rear
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0, 1);		glVertex3f(-0.75, -0.75, 1);
	glTexCoord2f(0, 0);		glVertex3f(-0.75, -0.75, 2);
	glTexCoord2f(1, 0);		glVertex3f(-1, -0.75, 2);
	glTexCoord2f(1, 1);		glVertex3f(-1, -0.75, 1);
	glEnd();

	// The sign textured
	glBegin(GL_QUADS);
	//  base top
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 1);		glVertex3f(1, 1, 3);
	glTexCoord2f(0, 0);		glVertex3f(-1, 1, 3);
	glTexCoord2f(1, 0);		glVertex3f(-1, -1, 3);
	glTexCoord2f(1, 1);		glVertex3f(1, -1, 3);

	// base bottom
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1, 1);		glVertex3f(1, -1, 2);
	glTexCoord2f(0, 1);		glVertex3f(-1, -1, 2);
	glTexCoord2f(0, 0);		glVertex3f(-1, 1, 2);
	glTexCoord2f(1, 0);		glVertex3f(1, 1, 2);

	// base left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 1);		glVertex3f(-1, 1, 3);
	glTexCoord2f(0, 0);		glVertex3f(-1, 1, 2);
	glTexCoord2f(1, 0);		glVertex3f(-1, -1, 2);
	glTexCoord2f(1, 1);		glVertex3f(-1, -1, 3);

	// base rear
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0, 1);		glVertex3f(1, -1, 2);
	glTexCoord2f(0, 0);		glVertex3f(1, -1, 3);
	glTexCoord2f(1, 0);		glVertex3f(-1, -1, 3);
	glTexCoord2f(1, 1);		glVertex3f(-1, -1, 2);

	// base front
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 1);		glVertex3f(1, 1, 3);
	glTexCoord2f(0, 0);		glVertex3f(1, 1, 2);
	glTexCoord2f(1, 0);		glVertex3f(-1, 1, 2);
	glTexCoord2f(1, 1);		glVertex3f(-1, 1, 3);

	if (!(image_data = (ubyte*)tga_load("ticketBooth.tga", &image_width,
		&image_height, TGA_TRUECOLOR_24)))
	{
		fprintf(stderr, "Ground::Initialize: Couldn't load grass.tga\n");
		return false;
	}

	glEnd();

	glGenTextures(1, &texture_obj);
	glBindTexture(GL_TEXTURE_2D, texture_obj);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image_width, image_height, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	glBegin(GL_QUADS);
	// base right
	glNormal3f(1.0f, 0.0f, 0.0f);
	// Idk why the texture coordinates are medded up here but I won't argue. Idc that much anyways.
	glTexCoord2f(1, 0);		glVertex3f(1, 1, 2);
	glTexCoord2f(1, 1);		glVertex3f(1, 1, 3);
	glTexCoord2f(0, 1);		glVertex3f(1, -1, 3);
	glTexCoord2f(0, 0);		glVertex3f(1, -1, 2);


	glEnd();


	// Turn texturing off again, because we don't want everything else to
	// be textured.
	glDisable(GL_TEXTURE_2D);
	glEndList();

	// We only do all this stuff once, when the GL context is first set up.
	initialized = true;

	return true;
}

void TicketBooth::Draw() {
	glPushMatrix();
	glTranslatef(25, -5, 0);
	glCallList(display_list);
	glPopMatrix();
}
