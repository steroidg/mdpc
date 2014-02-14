#include "mdpc.hpp"
#include "game.hpp"

/** @mainpage
 * This is an excercise to learn C++ while trying to see if my puzzle concept
 * would actually work.
 */

// Main function duh!
// This function should handle arguments and options spawn a game object
int main ( int argc, char * argv[] )
{
    Game * game_instance = new Game ();
    bool quit_game = game_instance->get_quit_game();
    
    while (quit_game == false) {
        quit_game = game_instance->get_quit_game();
    }
    
    delete ( game_instance );
    return 0;
}