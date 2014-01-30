#ifndef BASIC_DRAWABLE_OBJECT_H
#define BASIC_DRAWABLE_OBJECT_H
#include "mdpc.hpp"

class BasicDrawableObject
{
public:
    BasicDrawableObject ( Position p, Dimension d, int bpp );
    ~BasicDrawableObject ();
    sdl_surface_ptr get_surface ();
    Position get_position ();
    Dimension get_dimension ();
    void set_x ( int x );
    void set_y ( int y );
    void set_w ( int w );
    void set_h ( int h );

protected:
    sdl_surface_ptr surface;
    Position position;
    Dimension dimension;
    int bpp;
};

#endif