#include "player_character.hpp"
#include <iostream>

using namespace std;

PlayerCharacter::PlayerCharacter ( int x, int y, int w, int h, int bpp, int grid ) : BasicDrawableObject ( x, y, w, h,
bpp )
{
    surface = NULL;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->bpp = bpp;
    this->current_grid = grid;

    surface = SDL_CreateRGBSurface ( 0, w, h, bpp, 0, 0, 0, 0 );
    if ( surface == NULL ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: failed create surface."
             << endl;
    }

    Uint32 colour = SDL_MapRGB ( surface->format, 255, 255, 0 );
    if ( SDL_FillRect ( surface, &surface->clip_rect , colour ) == -1 ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: failed to fill grid colour."
             << endl;
    }
}

PlayerCharacter::~PlayerCharacter()
{
    SDL_FreeSurface ( surface );
}

int PlayerCharacter::get_current_grid()
{
    return current_grid;
}

void PlayerCharacter::set_grid ( int grid )
{
    this->current_grid = grid;
}