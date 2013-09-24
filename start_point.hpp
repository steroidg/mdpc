#include <SDL.h>
#include <iostream>

class StartPoint
{
public:
    StartPoint ( int x, int y, int w, int h, int grid );
    ~StartPoint();
    SDL_Surface * get_surface();
    int get_x();
    int get_y();
    int get_w();
    int get_h();
    int get_current_grid();
    void set_x ( int x );
    void set_y ( int y );
    void set_w ( int w );
    void set_h ( int h );
    void set_grid ( int grid );
private:
    SDL_Surface *surface;
    int x;
    int y;
    int w;
    int h;
    int current_grid;
};
