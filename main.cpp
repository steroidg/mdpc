#include <SDL.h>
#include <iostream>
#include "player_character.hpp"
#include "grid_unit.hpp"


using namespace std;

int main( int argc, char *argv[] )
{
	/* init variables */
	const int SCREEN_WIDTH	= 600;
	const int SCREEN_HEIGHT = 600;
	const int SCREEN_BPP = 32;
	const int GRID_SIZE = 60;
	bool quit = false;
	SDL_Event event;
	SDL_Surface *screen = NULL;
	
	/* init */
	SDL_Init( SDL_INIT_EVERYTHING );
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );
	
	int grid_x = SCREEN_WIDTH/GRID_SIZE;
	int grid_y = SCREEN_HEIGHT/GRID_SIZE;
	int grid_total = grid_x * grid_y;
	printf ("grid_x = %d, grid_y = %d, grid_total = %d.\n", grid_x, grid_y, grid_total);
	
	GridUnit ** gu_array = new GridUnit*[grid_total];
	int x = 0; 
	int y = 0; 
	for (int i = 0; i < grid_total; i++) {
		gu_array[i] = new GridUnit(x*GRID_SIZE, y*GRID_SIZE, GRID_SIZE, GRID_SIZE);
		y++;
		if (y == grid_y) {
			printf ("wtf\n");
			x++;
			y = 0;
		}
		printf ("i=%d, x=%d, y=%d\n", i, x, y);
	}
	
	PlayerCharacter * pc = new PlayerCharacter (0, 0, 50, 50);
	SDL_Surface *pc_surface = pc->get_surface();
	
	
	/* game loop */
	while ( quit == false ) {
		Uint32 bg_colour = SDL_MapRGB(screen->format, 0, 255, 255);
		if ( SDL_FillRect(screen, &screen->clip_rect, bg_colour) == -1 ) {
			printf ("%s %d ERROR: failed to fill background colour.\n", __PRETTY_FUNCTION__, __LINE__);
			return 1;
		} 
		
		for (int i = 0; i < grid_total; i++) {
			SDL_Rect gu_location = { gu_array[i]->get_x(), gu_array[i]->get_y(), gu_array[i]->get_w(), gu_array[i]->get_h()};
			//printf ("%s %d x=%d y=%d w=%d h=%d.\n", __PRETTY_FUNCTION__, __LINE__, gu_array[i]->get_x(), gu_array[i]->get_y(), gu_array[i]->get_w(), gu_array[i]->get_h());
			SDL_Surface * gu_surface = gu_array[i]->get_surface();
			if (gu_surface == NULL) {
				printf ("%s %d ERROR: failed to get gu_surface .\n", __PRETTY_FUNCTION__, __LINE__);
				return 1;
			}
			SDL_BlitSurface( gu_surface, NULL, screen, &gu_location );
		}
		
		SDL_Rect pc_location = { pc->get_x(), pc->get_y(), pc->get_w(), pc->get_h() };
		SDL_BlitSurface( pc_surface, NULL, screen, &pc_location );
		
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
	
	/* clean up */
	for (int i = 0; i < grid_total; i++) {
	  delete gu_array[i];
	}
	delete gu_array;
	delete pc;
	SDL_FreeSurface ( screen );
	SDL_Quit();
    
	return 0;
}
