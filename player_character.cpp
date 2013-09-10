#include "player_character.hpp"

PlayerCharacter::PlayerCharacter(int x, int y, int w, int h)
{
	surface = NULL;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	
	surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	
	if (surface == NULL) {
		printf ("%s %d ERROR: failed create surface.\n", __PRETTY_FUNCTION__, __LINE__);
	}
	Uint32 colour = SDL_MapRGB(surface->format, 255, 255, 0);
	if ( SDL_FillRect(surface, &surface->clip_rect , colour) == -1 ) {
		printf ("%s %d ERROR: failed to fill grid colour.\n", __PRETTY_FUNCTION__, __LINE__);
	}
}

PlayerCharacter::~PlayerCharacter()
{
	SDL_FreeSurface ( surface );
}

SDL_Surface* PlayerCharacter::get_surface()
{
	return surface;
}

int PlayerCharacter::get_x() {
	return x;
}

int PlayerCharacter::get_y() {
	return y;
}

int PlayerCharacter::get_w() {
	return w;
}

int PlayerCharacter::get_h() {
	return h;
}

void PlayerCharacter::set_x(int x)
{
	this->x = x;
}

void PlayerCharacter::set_y(int y)
{
	this->y = y;
}

void PlayerCharacter::set_w(int w)
{
	this->w = w;
}

void PlayerCharacter::set_h(int h)
{
	this->h = h;
}
