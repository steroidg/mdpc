#include "grid.hpp"

Grid::Grid ( int screen_x, int screen_y, int bpp, int grid_size_w, int grid_size_h, int grid_x, int grid_y, int
grid_total )
{
    this->screen_x = screen_x;
    this->screen_y = screen_y;
    this->bpp = bpp;
    this->grid_size_w= grid_size_w;
    this->grid_size_h = grid_size_h;
    this->grid_x = grid_x;
    this->grid_y = grid_y;
    this->grid_total = grid_total;
    
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
        gu_array.push_back ( grid_unit_ptr ( new GridUnit ( x*grid_size_w,
                                                            y*grid_size_h,
                                                            grid_size_w,
                                                            grid_size_h,
                                                            bpp )));
//        // new line
        x++;
        if ( x == grid_x ) {
            grid_map.push_back(row);
            row.clear();
            y++;
            x = 0;
        }
    }
    x = 0; y = 0;
    while (y < grid_y) {
        while (x < grid_x) {
            cout << "gu_array[grid_map[" << y << "][" << x << "]]->get_x() =" << gu_array[grid_map[y][x]]->get_x() <<
"\n" << endl;
            cout << "gu_array[grid_map[" << y << "][" << x << "]]->get_y() =" << gu_array[grid_map[y][x]]->get_y() <<
"\n" << endl;
            x++;
        }
        x = 0; 
        y++;
    }
}


Grid::~Grid()
{
}