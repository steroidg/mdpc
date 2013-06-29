#include <SDL.h>
#include <iostream>


using namespace std;

int main( int argc, char *argv[] )
{
	const int SCREEN_WIDTH	= 1024;
	const int SCREEN_HEIGHT = 480;
	const int SCREEN_BPP = 32;
	
	bool quit = false;
	SDL_Event event;
    SDL_Surface *screen = NULL;
	
    SDL_Init( SDL_INIT_EVERYTHING );
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );

	while ( quit == false ) {
		while( SDL_PollEvent( &event ) ) {
			if( event.type == SDL_QUIT ) {
				printf ("%s %d Quit event decected.\n", __PRETTY_FUNCTION__, __LINE__);
				quit = true;
			}
		}
	}
    
    SDL_FreeSurface ( screen );
    SDL_Quit();
    
	return 0;
}
