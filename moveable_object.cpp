#include "moveable_object.hpp"

MoveableObject::MoveableObject ( Position p, Dimension d, int bpp, int grid ): BasicDrawableObject ( p, d, bpp )
{
    this->position = p;
    this->dimension = d;
    this->bpp = bpp;
    this->current_grid = grid;

    surface = sdl_surface_ptr(SDL_CreateRGBSurface ( 0, dimension.w, dimension.h, bpp, 0, 0, 0, 0 ));
    if ( surface == NULL ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: failed create surface."
             << endl;
    }

    Uint32 colour = SDL_MapRGB ( surface->format, 255, 255, 0 );
    if ( SDL_FillRect ( &(*surface), &surface->clip_rect , colour ) == -1 ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: failed to fill grid colour."
             << endl;
    }
}

MoveableObject::~MoveableObject()
{
//    SDL_FreeSurface ( surface );
}

int MoveableObject::get_current_grid()
{
    return current_grid;
}

void MoveableObject::set_grid ( int grid )
{
    this->current_grid = grid;
}