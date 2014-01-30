#ifndef BASIC_DRAWABLE_OBJECT_H
#define BASIC_DRAWABLE_OBJECT_H
#include "mdpc.hpp"

class BasicDrawableObject
{
public:
    BasicDrawableObject ( position_ptr p, dimension_ptr d, int bpp );
    ~BasicDrawableObject ();
    sdl_surface_ptr get_surface ();
    position_ptr get_position ();
    dimension_ptr get_dimension ();
    void set_x ( int x );
    void set_y ( int y );
    void set_w ( int w );
    void set_h ( int h );

protected:
    sdl_surface_ptr surface;
    position_ptr position;
    dimension_ptr dimension;
    int bpp;
};

#endif