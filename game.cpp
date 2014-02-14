#include "game.hpp"

Game::Game ()
{
    quit_game   = false;
    
    game_screen = NULL;
    game_screen = init_game_screen ();
    if ( ! game_screen ) {
        cout << "ERROR: Unable to create game screen." << endl;
        quit_game = true;
    }
    
    game_grid = NULL;
    game_grid = init_game_grid ( game_screen );
    if ( ! game_grid ) {
        cout << "ERROR: Unable to create game grid." << endl;
        quit_game = true;
    }
    
    game_renderer = NULL;
    game_renderer = init_game_renderer ( game_screen );
    if ( ! game_renderer ) {
        cout << "ERROR: Unable to create game renderer." << endl;
        quit_game = true;
    }
    
    SDL_Delay(1000);
    quit_game = true;
}



Game::~Game()
{
    delete ( game_grid );
    delete ( game_renderer );
    SDL_FreeSurface ( game_screen );
    SDL_Quit();
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
    const int screen_width      = ( vinfo->current_w - 2 );
    const int screen_height     = ( vinfo->current_h - 100 );
    const int screen_bpp        = 32;

    SDL_Surface * screen = SDL_SetVideoMode ( screen_width,
                                              screen_height,
                                              screen_bpp,
                                              SDL_HWSURFACE );
    return screen;
}

Grid * Game::init_game_grid ( SDL_Surface * game_screen )
{
    Grid * game_grid = NULL;
    game_grid = new Grid ( game_screen->w,
                           game_screen->h,
                           game_screen->format->BitsPerPixel );
    return game_grid;
}

Renderer* Game::init_game_renderer ( SDL_Surface* game_screen )
{
    Renderer * game_renderer = NULL;
    game_renderer = new Renderer ();
    return game_renderer;
}
