#ifndef BASIC_DRAWABLE_OBJECT_H
#define BASIC_DRAWABLE_OBJECT_H
#include "mdpc.hpp"

class BasicDrawableObject
{
public:
    BasicDrawableObject ( vector<int> position, vector<int> dimension, int bpp );
    ~BasicDrawableObject ();
    sdl_surface_ptr get_surface ();
    vector<int> get_position ();
    vector<int> get_dimension ();
    void set_x ( int x );
    void set_y ( int y );
    void set_w ( int w );
    void set_h ( int h );

protected:
    sdl_surface_ptr surface;
    //TODO: maybe position and dimension should be struct or objects rather than vectors
    vector<int> position;
    vector<int> dimension;
    int bpp;
};

#endif