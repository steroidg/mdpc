#include "game.hpp"

Game::Game ()
{
    quit_game   = false;
    game_screen = NULL;
    game_screen = init_game_screen ();
    if ( ! game_screen ) {
        cout << "ERROR: Unable to create game screen\n" << endl;
        quit_game = true;
    }
    
    SDL_Delay(5000);
    quit_game = true;
}


Game::~Game()
{
}


bool Game::get_quit_game()
{
    return quit_game;
}


SDL_Surface * Game::init_game_screen ()
{
    if ( SDL_Init ( SDL_INIT_EVERYTHING ) < 0 ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: failed to init SDL."
             << endl;
        return NULL;
    }

    const SDL_VideoInfo * vinfo = SDL_GetVideoInfo();
    const int screen_width  = ( vinfo->current_w - 2 );
    const int screen_height = ( vinfo->current_h - 100 );
    const int screen_bpp    = 32;

    SDL_Surface * screen = SDL_SetVideoMode ( screen_width,
                                              screen_height,
                                              screen_bpp,
                                              SDL_HWSURFACE );
    return screen;
}
