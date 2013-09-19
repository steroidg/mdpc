#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include "player_character.hpp"
#include "grid_unit.hpp"


using namespace std;

int player_location ( int x, int y, int w, int h, GridUnit ** gu_array, int grid_total )
{
    int player_location = 0;
    int pc_centre_x = x + ( w/2 );
    int pc_centre_y = y + ( h/2 );

    for ( int i = 0; i < grid_total; i++ ) {
        player_location = i;
        printf ( "pc_centre_x = %d, gu_array[i]->get_x() = %d, gu_array[i]->get_w() = %d\n",
                 pc_centre_x,
                 gu_array[i]->get_x(),
                 gu_array[i]->get_w()
               );
        printf ( "pc_centre_y = %d, gu_array[i]->get_y() = %d, gu_array[i]->get_h() = %d\n", pc_centre_y,
                 gu_array[i]->get_y(), gu_array[i]->get_h() );
        if ( pc_centre_x >= gu_array[i]->get_x() &&
                pc_centre_x < ( gu_array[i]->get_x() + gu_array[i]->get_w() ) &&
                pc_centre_y >= gu_array[i]->get_y() &&
                pc_centre_y < ( gu_array[i]->get_y() + gu_array[i]->get_h() ) ) {
            printf ( "i = %d\n", i );
            break;
        }
    }
    return player_location;
}

int main ( int argc, char *argv[] )
{
    /* init variables */
    const int SCREEN_WIDTH	= 600;
    const int SCREEN_HEIGHT = 600;
    const int SCREEN_BPP = 32;
    const int GRID_SIZE_W = 60;
    const int GRID_SIZE_H = 50;
    bool quit = false;
    SDL_Event event;
    SDL_Surface *screen = NULL;

    TTF_Init();
    SDL_Surface * on_screen_display = NULL;
    TTF_Font *font = NULL;
    SDL_Color textColor = { 0, 255, 0 };
    font = TTF_OpenFont ( "/home/billy/Dropbox/devel/mdpc/Ubuntu-B.ttf", 36 );
    printf ( "TTF ERROR: %s\n", TTF_GetError() );
    if ( font == NULL ) {
        printf ( "wtf font!.\n" );
        return 1;
    }

    /* init */
    SDL_Init ( SDL_INIT_EVERYTHING );
    screen = SDL_SetVideoMode ( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );

    int grid_x = SCREEN_WIDTH/GRID_SIZE_W;
    int grid_y = SCREEN_HEIGHT/GRID_SIZE_H;
    int grid_total = grid_x * grid_y;
    printf ( "grid_x = %d, grid_y = %d, grid_total = %d.\n", grid_x, grid_y, grid_total );

    GridUnit ** gu_array = new GridUnit*[grid_total];
    int x = 0;
    int y = 0;
    for ( int i = 0; i < grid_total; i++ ) {
        gu_array[i] = new GridUnit ( x*GRID_SIZE_W, y*GRID_SIZE_H, GRID_SIZE_W, GRID_SIZE_H );
        y++;
        if ( y == grid_y ) {
            printf ( "wtf\n" );
            x++;
            y = 0;
        }
        printf ( "i=%d, x=%d, y=%d\n", i, x, y );
    }

    PlayerCharacter * pc = new PlayerCharacter ( 220, 240, GRID_SIZE_W, GRID_SIZE_H );
    SDL_Surface *pc_surface = pc->get_surface();


    /* game loop */

    int counter= 0;
    while ( quit == false ) {
        while ( SDL_PollEvent ( &event ) ) {
            Uint8 *keystates = SDL_GetKeyState( NULL );
            if ( keystates[ SDLK_UP ] ) {
                pc->set_y ( pc->get_y() - 1 );
            }
            //If down is pressed
            if ( keystates[ SDLK_DOWN ] ) {
                pc->set_y ( pc->get_y() + 1 );
            } 
            //If left is pressed
            if ( keystates[ SDLK_LEFT ] ) {
                pc->set_x ( pc->get_x() - 1 );
            }
            //If right is pressed
            if ( keystates[ SDLK_RIGHT ] ) {
                pc->set_x ( pc->get_x() + 1 );
            }
            if ( event.type == SDL_QUIT ) {
                printf ( "%s %d Quit event decected.\n", __PRETTY_FUNCTION__, __LINE__ );
                quit = true;
            }
        }
        stringstream osd_str;
        osd_str << "count" << counter;
        std::string boo = osd_str.str();
        const char * whoa = boo.c_str();

        on_screen_display = TTF_RenderText_Solid ( font, whoa, textColor );
        SDL_Rect osd_location = {50, 50, 300, 100};


        Uint32 bg_colour = SDL_MapRGB ( screen->format, 0, 255, 255 );
        if ( SDL_FillRect ( screen, &screen->clip_rect, bg_colour ) ==
                -1 ) {
            printf ( "%s %d ERROR: failed to fill background colour.\n", __PRETTY_FUNCTION__, __LINE__ );
            return 1;
        }

        for ( int i = 0; i < grid_total; i++ ) {
            SDL_Rect gu_location = { gu_array[i]->get_x(), gu_array[i]->get_y(), gu_array[i]->get_w(),
                                     gu_array[i]->get_h()
                                   };
            //printf ("%s %d x=%d y=%d w=%d h=%d.\n", __PRETTY_FUNCTION__, __LINE__, gu_array[i]->get_x(),
            gu_array[i]->get_y(), gu_array[i]->get_w(), gu_array[i]->get_h();
            SDL_Surface * gu_surface = gu_array[i]->get_surface();
            if ( gu_surface == NULL ) {
            printf ( "%s %d ERROR: failed to get gu_surface .\n", __PRETTY_FUNCTION__, __LINE__ );
                return 1;
            }
            SDL_BlitSurface ( gu_surface, NULL, screen, &gu_location );
        }

        SDL_Rect pc_location = { pc->get_x(), pc->get_y(), pc->get_w(), pc->get_h() };
//        int pc_grid = player_location ( pc->get_x(), pc->get_y(), pc->get_w(), pc->get_h(), gu_array, grid_total );
//        gu_array[pc_grid]->set_colour ( 255,255,255 );
        SDL_BlitSurface ( pc_surface, NULL, screen, &pc_location );
        SDL_BlitSurface ( on_screen_display, NULL, screen, &osd_location );

        if ( SDL_Flip ( screen ) == -1 ) {
            printf ( "%s %d ERROR: failed to flip.\n", __PRETTY_FUNCTION__, __LINE__ );
            return 1;
        }

        counter++;
        SDL_Delay ( 100 );
    }

    /* clean up */
    for ( int i = 0; i < grid_total; i++ ) {
        delete gu_array[i];
    }
    delete gu_array;
    delete pc;
    TTF_CloseFont ( font );
    SDL_FreeSurface ( screen );
    SDL_Quit();

    return 0;
}
