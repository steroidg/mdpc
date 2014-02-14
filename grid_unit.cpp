#include "grid_unit.hpp"

GridUnit::GridUnit ( Position2D p, Dimension2D d, int bpp ) : BasicDrawableObject ( p, d, bpp )
{
    this->position = p;
    this->dimension = d;
    this->bpp = bpp;

    surface = SDL_CreateRGBSurface ( 0, dimension.w, dimension.h, bpp, 0, 0, 0, 0 );
    if ( surface == NULL ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: failed create surface."
             << endl;
    }
}


GridUnit::~GridUnit()
{
    SDL_FreeSurface ( surface );
}

void GridUnit::set_colour(RGB_colour * colour)
{
    this->colour = colour;
}