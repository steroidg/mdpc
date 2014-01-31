#ifndef MOVEABLE_OBJECT_H
#define MOVEABLE_OBJECT_H
#include "mdpc.hpp"
#include "basic_drawable_object.hpp"

class MoveableObject: public BasicDrawableObject
{
public:
    MoveableObject ( Position p, Dimension d, int bpp, int grid );
    ~MoveableObject();
    int get_current_grid();
    void set_grid ( int grid );
private:
    int current_grid;
};
#endif