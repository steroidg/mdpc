#include "basic_drawable_object.hpp"
#include <iostream>

using namespace std;

BasicDrawableObject::BasicDrawableObject ( int x, int y, int w, int h, int bpp )
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->bpp = bpp;
    surface = NULL;

    surface = SDL_CreateRGBSurface ( 0, w, h, bpp, 0, 0, 0, 0 );
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

SDL_Surface* BasicDrawableObject::get_surface()
{
    return surface;
}

int BasicDrawableObject::get_x()
{
    return x;
}

int BasicDrawableObject::get_y()
{
    return y;
}

int BasicDrawableObject::get_w()
{
    return w;
}

int BasicDrawableObject::get_h()
{
    return h;
}

void BasicDrawableObject::set_x ( int x )
{
    this->x = x;
}

void BasicDrawableObject::set_y ( int y )
{
    this->y = y;
}

void BasicDrawableObject::set_w ( int w )
{
    this->w = w;
}

void BasicDrawableObject::set_h ( int h )
{
    this->h = h;
}
