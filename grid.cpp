#include "grid.hpp"

Grid::Grid ( int screen_x, int screen_y, int bpp )
{
    // Grid related variables
    int grid_x = 32; // magic number for grid columns (x axis)
    int grid_y = 18; // magic number for grid rows (y axis)
    int grid_total = grid_x * grid_y; // total number of grid units
    
    this->grid_dimension.w = screen_x / grid_x;
    this->grid_dimension.h = screen_y / grid_y;
    gu_array.clear();
    
    cout << "screen_x = "   << screen_x << "\n"
         << "screen_y = "   << screen_y << "\n"
         << "bpp = "        << bpp << "\n"
         << "grid_x = "     << grid_x << "\n"
         << "grid_y = "     << grid_y << "\n"
         << "grid_total = " << grid_total << "\n"
         << endl;
    
    int x = 0, y = 0;
    vector<int> row;
    for ( int i = 0; i < grid_total; i++ ) {
        row.push_back(i);
        
        Position2D p;
        p.x = x * grid_dimension.w;
        p.y = y * grid_dimension.h;
        
        gu_array.push_back ( new GridUnit ( p, grid_dimension, bpp ) );
        
        // new line
        x++;
        if ( x == grid_x ) {
            grid_map.push_back(row);
            row.clear();
            y++;
            x = 0;
        }
    }
}


Grid::~Grid()
{
    while (!gu_array.empty()) {
        delete gu_array.back();
        gu_array.pop_back();
    }
}

vector< vector< int > > Grid::get_grid_map()
{
    return grid_map;
}

Dimension2D Grid::get_grid_dimension()
{
    return grid_dimension;
}

std::vector< GridUnit* > Grid::get_gu_array()
{
    return gu_array;
}
