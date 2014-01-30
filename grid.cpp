#include "grid.hpp"

Grid::Grid ( int screen_x, int screen_y, int bpp )
{
    // Grid related variables
    grid_x = 32; // magic number for grid columns (x axis)
    grid_y = 18; // magic number for grid rows (y axis)
    grid_total = grid_x * grid_y; // total number of grid units
    
    this->screen_x = screen_x;
    this->screen_y = screen_y;
    this->bpp = bpp;
    this->grid_size_w = screen_x / grid_x;
    this->grid_size_h = screen_y / grid_y;
    
    cout << "screen_x = " << screen_x << "\n"
         << "screen_y = " << screen_y << "\n"
         << "bpp = " << bpp << "\n"
         << "grid_x = " << grid_x << "\n"
         << "grid_y = " << grid_y << "\n"
         << "grid_total = " << grid_total << "\n"
         << endl;
    
    int x = 0, y = 0;
    vector<int> row;
    for ( int i = 0; i < grid_total; i++ ) {
        row.push_back(i);
        Position p;
        p.x = x * grid_size_w;
        p.y = y * grid_size_h;
        
        Dimension d;
        d.w = grid_size_w;
        d.h = grid_size_h;
        gu_array.push_back ( grid_unit_ptr ( new GridUnit ( p, d, bpp )));
//        // new line
        x++;
        if ( x == grid_x ) {
            grid_map.push_back(row);
            row.clear();
            y++;
            x = 0;
        }
    }
//    x = 0; y = 0;
//    while (y < grid_y) {
//        while (x < grid_x) {
//            cout << "gu_array[grid_map[" << y << "][" << x << "]]->get_x() =" << gu_array[grid_map[y][x]]->get_x() <<
//"\n" << endl;
//            cout << "gu_array[grid_map[" << y << "][" << x << "]]->get_y() =" << gu_array[grid_map[y][x]]->get_y() <<
//"\n" << endl;
//            x++;
//        }
//        x = 0; 
//        y++;
//    }
}


Grid::~Grid()
{
}

vector< grid_unit_ptr > Grid::get_grid_units()
{
    return gu_array;
}

vector< vector< int > > Grid::get_grid_map()
{
    return grid_map;
}

int Grid::get_grid_width ()
{
    return grid_size_w; 
}

int Grid::get_grid_height ()
{
    return grid_size_h; 
}

int Grid::get_grid_total()
{
    return grid_total;
}
