#ifndef GRID_H
#define GRID_H
#include "mdpc.hpp"
#include "grid_unit.hpp"

typedef boost::shared_ptr<GridUnit> grid_unit_ptr;

class Grid
{
public:
    Grid ( int screen_x, int screen_y, int bpp, int grid_size_w, int grid_size_h, int grid_x, int grid_y, int grid_total
);
    ~Grid ();
private:
    vector< vector<int> > grid_map;
    vector< grid_unit_ptr > gu_array;
    int screen_x;
    int screen_y;
    int bpp;
    int grid_size_w;
    int grid_size_h;
    int grid_x;
    int grid_y;
    int grid_total;
};
#endif
