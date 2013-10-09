#ifndef GRID_UNIT_H
#define GRID_UNIT_H
#include "basic_drawable_object.hpp"

class GridUnit: public BasicDrawableObject
{
public:
    GridUnit ( int x, int y, int w, int h, int bpp );
    ~GridUnit ();
    void set_colour ( int r, int g, int b );
private:
    void render ( int r, int g, int b );
};
#endif
