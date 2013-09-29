#include "grid_unit.hpp"
#include <iostream>

using namespace std;

GridUnit::GridUnit ( int x, int y, int w, int h, int bpp ) : BasicDrawableObject ( x, y, w, h, bpp )
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
    
    this->render(0, 0, 150);
}

GridUnit::~GridUnit()
{
    SDL_FreeSurface ( surface );
}

void GridUnit::render(int r, int g, int b) {
	Uint32 colour = SDL_MapRGB(surface->format, r, g, b);
	if ( SDL_FillRect(surface, &surface->clip_rect , colour) == -1 ) {
		printf ("%s %d ERROR: failed to fill grid colour.\n", __PRETTY_FUNCTION__, __LINE__);
	}
}

void GridUnit::set_colour(int r, int g, int b)
{
	this->render (r, g, b);
}