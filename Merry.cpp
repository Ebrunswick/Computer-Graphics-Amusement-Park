#include "Merry.h"
#include "libtarga.h"
#include <cstdio>
#include <gl/GLU.h>

Merry::~Merry(void) {
    if (initialized)
    {
        glDeleteLists(display_list, 1);
        glDeleteTextures(1, &texture_obj);
    }
}

bool Merry::Initialize(void) {
    ubyte* image_data;
    int	    image_height, image_width;
    GLUquadric* quadratic_obj = gluNewQuadric();
    base_radius = 5;
    column_radius = 0.5;
    float column_height = 3;

    gluQuadricNormals(quadratic_obj, GLU_SMOOTH);

    // Load the image for the texture. The texture file has to be in
    // a place where it will be found.
    if (!(image_data = (ubyte*)tga_load("stripes.tga", &image_width,
        &image_height, TGA_TRUECOLOR_24)))
    {
        fprintf(stderr, "Sphere::Initialize: Couldn't load Steel2.tga\n");
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


    glBindTexture(GL_TEXTURE_2D, texture_obj);
    glColor3f(1, 1, 1);
    gluQuadricDrawStyle(quadratic_obj, GLU_FILL);

    gluQuadricTexture(quadratic_obj, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    gluCylinder(quadratic_obj, base_radius, base_radius, 1, 32, 16);
    glTranslatef(0, 0, 1);
    gluDisk(quadratic_obj, 0, base_radius, 36, 16);


    gluCylinder(quadratic_obj, column_radius * 2, column_radius * 2, column_height, 32, 16);
    glTranslatef(4.5, 0, 0);
    gluCylinder(quadratic_obj, column_radius, column_radius, column_height, 32, 16);
    glTranslatef(-9, 0, 0);
    gluCylinder(quadratic_obj, column_radius, column_radius, column_height, 32, 16);
    glTranslatef(4.5, 4.5, 0);
    gluCylinder(quadratic_obj, column_radius, column_radius, column_height, 32, 16);
    glTranslatef(0, -9, 0);
    gluCylinder(quadratic_obj, column_radius, column_radius, column_height, 32, 16);
    glDisable(GL_TEXTURE_2D);
    gluQuadricTexture(quadratic_obj, GL_FALSE);

    if (!(image_data = (ubyte*)tga_load("carnival.tga", &image_width,
        &image_height, TGA_TRUECOLOR_24)))
    {
        fprintf(stderr, "Sphere::Initialize: Couldn't load Steel2.tga\n");
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



    gluQuadricTexture(quadratic_obj, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(0, 4.5, column_height);
    glRotatef(180, 1, 0, 0);
    gluDisk(quadratic_obj, 0, base_radius, 32, 16);
    glRotatef(180, 1, 0, 0);
    gluCylinder(quadratic_obj,base_radius, 0, 2, 32, 16);
    glDisable(GL_TEXTURE_2D);
    gluQuadricTexture(quadratic_obj, GL_FALSE);

    glEndList();

    initialized = true;
    return true;
}

void Merry::Draw(void) {
    glPushMatrix();
    glTranslatef(-30, 30, 0);
    glCallList(display_list);
    glPopMatrix();
}