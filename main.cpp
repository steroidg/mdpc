#include <SDL.h>
#include <iostream>
#include "player_character.hpp"
#include "grid_unit.hpp"


using namespace std;

int main( int argc, char *argv[] )
{
	const int SCREEN_WIDTH	= 600;
	const int SCREEN_HEIGHT = 600;
	const int SCREEN_BPP = 32;
	
	bool quit = false;
	SDL_Event event;
	SDL_Surface *screen = NULL;
	SDL_Surface *player = NULL;
	
    SDL_Init( SDL_INIT_EVERYTHING );
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );
	player = SDL_CreateRGBSurface(0, 60, 60, 32, 0, 0, 0, 0);
	if ( player == NULL) {
		printf ("%s %d ERROR: failed to create player surface.\n", __PRETTY_FUNCTION__, __LINE__);
		return 1;
	}
	
	
	GridUnit *gu = new GridUnit(60, 0, 60, 60);
	
	while ( quit == false ) {
		Uint32 bg_colour = SDL_MapRGB(screen->format, 0, 255, 255);
		if ( SDL_FillRect(screen, &screen->clip_rect, bg_colour) == -1 ) {
				printf ("%s %d ERROR: failed to fill background colour.\n", __PRETTY_FUNCTION__, __LINE__);
				return 1;
		} 
		
		Uint32 block_colour = SDL_MapRGB(player->format, 0, 0, 255);
		SDL_Rect block_location = { 0, 60, 60, 60 };
		if ( SDL_FillRect(player, &player->clip_rect , block_colour) == -1 ) {
				printf ("%s %d ERROR: failed to fill player colour.\n", __PRETTY_FUNCTION__, __LINE__);
				return 1;
		} 
		SDL_BlitSurface( player, NULL, screen, &block_location );
		
		SDL_Rect gu_location = { gu->get_x(), gu->get_y(), gu->get_w(), gu->get_h()};
		SDL_Surface * gu_surface = gu->get_surface();
		if (gu_surface == NULL) {
				printf ("%s %d ERROR: failed to get gu_surface .\n", __PRETTY_FUNCTION__, __LINE__);
				return 1;
		}
		SDL_BlitSurface( gu_surface, NULL, screen, &gu_location );
		
		if ( SDL_Flip(screen) == -1 ) {
				printf ("%s %d ERROR: failed to flip.\n", __PRETTY_FUNCTION__, __LINE__);
				return 1;
		}
		
		while( SDL_PollEvent( &event ) ) {
			if( event.type == SDL_QUIT ) {
				printf ("%s %d Quit event decected.\n", __PRETTY_FUNCTION__, __LINE__);
				quit = true;
			}
		}
	}
	
	delete gu;
	SDL_FreeSurface ( screen );
	SDL_FreeSurface ( player );
	SDL_Quit();
    
	return 0;
}
