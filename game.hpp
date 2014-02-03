#ifndef GAME_H
#define GAME_H
#include "mdpc.hpp"

class Game
{
    public:
        Game ();
        ~Game ();
        bool get_quit_game ();
        
    private:
        SDL_Surface * init_game_screen ();
        bool quit_game;
        SDL_Surface * game_screen;
};

#endif