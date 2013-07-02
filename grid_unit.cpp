#include "grid_unit.hpp"

GridUnit::GridUnit(int x, int y, int w, int h)
{
	surface = NULL;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = y;
	
	surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	
	if (surface == NULL) {
		printf ("%s %d ERROR: failed create surface.\n", __PRETTY_FUNCTION__, __LINE__);
	}
	Uint32 colour = SDL_MapRGB(surface->format, 0, 255, 0);
	if ( SDL_FillRect(surface, &surface->clip_rect , colour) == -1 ) {
		printf ("%s %d ERROR: failed to fill grid colour.\n", __PRETTY_FUNCTION__, __LINE__);
	}
	printf ("%s %d %d %d %d %d wee!.\n", __PRETTY_FUNCTION__, __LINE__, x, y, h, w);
}

GridUnit::~GridUnit()
{
	SDL_FreeSurface ( surface );
	printf ("%s %d deleted.\n", __PRETTY_FUNCTION__, __LINE__);
}

SDL_Surface * GridUnit::get_surface() {
	return surface;
}

int GridUnit::get_x() {
	return x;
}

int GridUnit::get_y() {
	return y;
}

int GridUnit::get_w() {
	return w;
}

int GridUnit::get_h() {
	return h;
}
