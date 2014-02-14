#include "basic_drawable_object.hpp"

BasicDrawableObject::BasicDrawableObject ( Position2D p, Dimension2D d, int bpp )
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

BasicDrawableObject::~BasicDrawableObject()
{
    SDL_FreeSurface ( surface );
}

SDL_Surface * BasicDrawableObject::get_surface()
{
    return surface;
}

Position2D BasicDrawableObject::get_position()
{
    return position;
}

Dimension2D BasicDrawableObject::get_dimension()
{
    return dimension;
}

void BasicDrawableObject::set_x ( int x )
{
    this->position.x = x;
}

void BasicDrawableObject::set_y ( int y )
{
    this->position.y = y;
}

void BasicDrawableObject::set_w ( int w )
{
    this->dimension.w = w;
}

void BasicDrawableObject::set_h ( int h )
{
    this->dimension.h = h;
}
