#ifndef GAME_H
#define GAME_H
#include "mdpc.hpp"
#include "grid.hpp"
#include "renderer.hpp"

class Game
{
    public:
        /** Constructor  */
        Game ();
        /** Destructor */
        ~Game ();
        /** Function that returns the game state */
        bool get_quit_game ();
        
    private:
        /** Initialize the main game screen */
        SDL_Surface * init_game_screen ();
        /** Initialize the game grid */
        Grid * init_game_grid ( SDL_Surface * game_screen );
        /** Initialize the game renderer */
        Renderer * init_game_renderer (SDL_Surface * game_screen);
        
        /** Boolean variable to indicate whether to quit or not */
        bool quit_game;
        /** Game screen object */
        SDL_Surface * game_screen;
        /** Game grid object */
        Grid * game_grid;
        Renderer * game_renderer;
};

#endif