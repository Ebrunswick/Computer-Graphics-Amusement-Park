#ifndef _WALL_H_
#define _WALL_H_

#include <Fl/gl.h>

class Wall {
private:
    // Members
    GLubyte display_list;   // The display list that does all the work.
    GLuint  texture_obj;    // The object for the grass texture.
    bool    initialized;    // Whether or not we have been initialised.
    float   wall_length, wall_width, wall_height;
    float   x_coordinate, y_coordinate, z_coordinate;

    // Methods
    void    Initialize_Object(float length, float width, float height);


public:

    Wall(void) { display_list = 0; initialized = false; };
    Wall(float l, float w, float h) { display_list = 0; initialized = false; wall_length = l; wall_width = w; wall_height = h; x_coordinate = y_coordinate = z_coordinate = 0; };
    ~Wall(void);
    bool    Initialize(void);
    void    Draw(void);
    void    SetCoordinates(float x, float y, float z) { x_coordinate = x; y_coordinate = y; z_coordinate = z;}
};


#endif