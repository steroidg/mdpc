#include "basic_drawable_object.hpp"

BasicDrawableObject::BasicDrawableObject ( vector<int> position, vector<int> dimension, int bpp )
{
    this->position = position;
    this->dimension = dimension;
    this->bpp = bpp;

    // TODO: dimension need to have width and height defined
    surface = sdl_surface_ptr(SDL_CreateRGBSurface ( 0, dimension[0], dimension[1], bpp, 0, 0, 0, 0 ));
    if ( surface == NULL ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: failed create surface."
             << endl;
    }
}

BasicDrawableObject::~BasicDrawableObject()
{
//    SDL_FreeSurface ( surface );
}

sdl_surface_ptr BasicDrawableObject::get_surface()
{
    return surface;
}

vector< int > BasicDrawableObject::get_position()
{
    return position;
}

vector< int > BasicDrawableObject::get_dimension()
{
    return dimension;
}

void BasicDrawableObject::set_x ( int x )
{
    this->position[0] = x;
}

void BasicDrawableObject::set_y ( int y )
{
    this->position[1] = y;
}

void BasicDrawableObject::set_w ( int w )
{
    this->dimension[0] = w;
}

void BasicDrawableObject::set_h ( int h )
{
    this->dimension[1] = h;
}
