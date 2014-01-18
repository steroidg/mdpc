#include "grid.hpp"

Grid::Grid ( int screen_x, int screen_y, int bpp, int grid_size_w, int grid_size_h, int grid_total )
{
    this->screen_x = screen_x;
    this->screen_y = screen_y;
    this->bpp = bpp;
    this->grid_size_w = grid_size_w;
    this->grid_size_h = grid_size_h;
    this->grid_total = grid_total;
    
    int x = 0, y = 0;
    for ( int i = 0; i < grid_total; i++ ) {
        grid_map[x][y]=i;
        gu_array.push_back ( grid_unit_ptr ( new GridUnit ( x*grid_size_w,
                                                            y*grid_size_h,
                                                            grid_size_w,
                                                            grid_size_h,
                                                            bpp )));
        x++;
        // new line
        if ( x == screen_x ) {
            y++;
            x = 0;
        }
    }
}


Grid::~Grid()
{
}