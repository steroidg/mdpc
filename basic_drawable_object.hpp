#ifndef BASIC_DRAWABLE_OBJECT_H
#define BASIC_DRAWABLE_OBJECT_H
#include "mdpc.hpp"

class BasicDrawableObject
{
public:
    BasicDrawableObject ( int x, int y, int w, int h, int bpp );
    ~BasicDrawableObject ();
    sdl_surface_ptr get_surface ();
    int get_x ();
    int get_y ();
    int get_w ();
    int get_h ();
    void set_x ( int x );
    void set_y ( int y );
    void set_w ( int w );
    void set_h ( int h );

protected:
    sdl_surface_ptr surface;
    int x;
    int y;
    int w;
    int h;
    int bpp;
};

#endif
