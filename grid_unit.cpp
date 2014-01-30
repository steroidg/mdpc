#include "grid_unit.hpp"

GridUnit::GridUnit ( position_ptr p, dimension_ptr d, int bpp ) : BasicDrawableObject ( p, d, bpp )
{
    this->position = p;
    this->dimension = d;
    this->bpp = bpp;

    surface = sdl_surface_ptr(SDL_CreateRGBSurface ( 0, dimension->w, dimension->h, bpp, 0, 0, 0, 0 ));
    if ( surface == NULL ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: failed create surface."
             << endl;
    }
    
    this->render(0, 150, 150);
}


GridUnit::~GridUnit()
{
//    SDL_FreeSurface ( surface );
}

void GridUnit::render(int r, int g, int b) {
	Uint32 colour = SDL_MapRGB(surface->format, r, g, b);
	if ( SDL_FillRect(&(*surface), &surface->clip_rect , colour) == -1 ) {
		printf ("%s %d ERROR: failed to fill grid colour.\n", __PRETTY_FUNCTION__, __LINE__);
	}
}

void GridUnit::set_colour(int r, int g, int b)
{
	this->render (r, g, b);
}