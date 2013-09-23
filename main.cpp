#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "player_character.hpp"
#include "grid_unit.hpp"

#define GRID_UP 1
#define GRID_DOWN 2
#define GRID_LEFT 3
#define GRID_RIGHT 4

using namespace std;


// This function goes through the grids to find out which grid
// is the player characeter currently located. Not sure if needed
int player_location ( int x,
                      int y,
                      int w,
                      int h,
                      GridUnit ** gu_array,
                      int grid_total )
{
    int player_location = 0;
    int pc_centre_x = x + ( w/2 );
    int pc_centre_y = y + ( h/2 );

    for ( int i = 0; i < grid_total; i++ ) {
        player_location = i;
        if ( pc_centre_x >= gu_array[i]->get_x() &&
                pc_centre_x < ( gu_array[i]->get_x() + gu_array[i]->get_w() ) &&
                pc_centre_y >= gu_array[i]->get_y() &&
                pc_centre_y < ( gu_array[i]->get_y() + gu_array[i]->get_h() ) ) {
            break;
        }
    }
    return player_location;
}


// This function returns a SDC_Rect based on the location of an object and size
// of a grid
SDL_Rect get_pc_location ( int grid_x,
                           int grid_y,
                           int grid_w,
                           int grid_h,
                           int pc_w,
                           int pc_h )
{
    int pc_x = grid_x + grid_w/2 - pc_w / 2;
    int pc_y = grid_y + grid_h/2 - pc_h / 2;
    SDL_Rect retval = { pc_x, pc_y, pc_w, pc_h };

    return retval;
}


// This function gets the grid map, current grid and the direction to move
// and return the destination grid if movement is possible
int process_grid_map ( vector< vector<int> > &grid_map, int current_grid, int direction )
{
    int grid_x = grid_map.size();
    int grid_y = grid_map[0].size();
    int retval = 5;

    for ( int i=0; i<grid_y; i++ ) {
        for ( int j=0; j<grid_x; j++ ) {
            if ( current_grid == grid_map[j][i] ) {
                cout << "grid_map[" <<j << "][" << i << "] = " << grid_map[j][i] << '\n';
                switch ( direction ) {
                case GRID_UP:
                    if ( i > 0 ) {
                        retval = grid_map[j][i-1];
                    } else {
                        retval = current_grid;
                    }
                    break;
                case GRID_DOWN:
                    if ( i < ( grid_y-1 ) ) {
                        retval = grid_map[j][i+1];
                    } else {
                        retval = current_grid;
                    }
                    break;
                case GRID_LEFT:
                    if ( j > 0 ) {
                        retval = grid_map[j-1][i];
                    } else {
                        retval = current_grid;
                    }
                    break;
                case GRID_RIGHT:
                    if ( j < ( grid_x-1 ) ) {
                        cout << "got here\n";
                        retval = grid_map[j+1][i];
                    } else {
                        retval = current_grid;
                    }
                    break;
                default:
                    retval = current_grid;
                }
            }
        }
    }
    return retval;
}


// Main function duh!
int main ( int argc, char *argv[] )
{
    /* init variables */
    const int SCREEN_WIDTH = 600;
    const int SCREEN_HEIGHT = 600;
    const int SCREEN_BPP = 32;
    const int GRID_SIZE_W = 50;
    const int GRID_SIZE_H = 40;
    const int PC_SIZE_W = 40;
    const int PC_SIZE_H = 40;
    bool quit = false;
    SDL_Event event;
    SDL_Surface *screen = NULL;
    SDL_Surface *osd = NULL;
    TTF_Font *osd_font = NULL;


    /* init */
    SDL_Init ( SDL_INIT_EVERYTHING );
    screen = SDL_SetVideoMode ( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );
    if ( screen == NULL ) {
        printf ( "%s %d ERROR: Unable to load screen.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }

    TTF_Init();
    SDL_Color osd_text_colour = { 0, 255, 0 };
    osd_font = TTF_OpenFont ( "/home/billy/Dropbox/devel/mdpc/Ubuntu-B.ttf", 14 );
    if ( osd_font == NULL ) {
        printf ( "%s %d ERROR: Unable to load font.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }

    int grid_x = SCREEN_WIDTH/GRID_SIZE_W;
    int grid_y = SCREEN_HEIGHT/GRID_SIZE_H;
    int grid_total = grid_x * grid_y;
    vector< vector<int> > grid_map ( grid_x, vector<int> ( grid_y ) );

    GridUnit ** gu_array = new GridUnit*[grid_total];
    int x = 0, y = 0;
    for ( int i = 0; i < grid_total; i++ ) {
        grid_map[x][y] = i;
        gu_array[i] = new GridUnit ( x*GRID_SIZE_W, y*GRID_SIZE_H, GRID_SIZE_W, GRID_SIZE_H );
        x++;
        if ( x == grid_x ) {
            y++;
            x = 0;
        }
    }

    PlayerCharacter * pc = new PlayerCharacter ( 0, 0, PC_SIZE_W, PC_SIZE_H, 4 );
    SDL_Surface *pc_surface = pc->get_surface();
    if ( pc_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load pc_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }

    PlayerCharacter * pc_mirror = new PlayerCharacter ( 0, 0, PC_SIZE_W - 10, PC_SIZE_H - 10, 28 );
    SDL_Surface *pc_mirror_surface = pc_mirror->get_surface();
    if ( pc_mirror_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load pc_mirror_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }
    /* game loop */
    int counter= 0;
    while ( quit == false ) {
        // Event handler
        while ( SDL_PollEvent ( &event ) ) {
            Uint8 *keystates = SDL_GetKeyState ( NULL );
            if ( keystates[ SDLK_UP ] ) {
                pc->set_grid ( process_grid_map ( grid_map, pc->get_current_grid(), GRID_UP ) );
                pc_mirror->set_grid ( process_grid_map ( grid_map, pc_mirror->get_current_grid(), GRID_DOWN ) );
            }
            //If down is pressed
            if ( keystates[ SDLK_DOWN ] ) {
                pc->set_grid ( process_grid_map ( grid_map, pc->get_current_grid(), GRID_DOWN ) );
                pc_mirror->set_grid ( process_grid_map ( grid_map, pc_mirror->get_current_grid(), GRID_UP ) );
            }
            //If left is pressed
            if ( keystates[ SDLK_LEFT ] ) {
                pc->set_grid ( process_grid_map ( grid_map, pc->get_current_grid(), GRID_LEFT ) );
                pc_mirror->set_grid ( process_grid_map ( grid_map, pc_mirror->get_current_grid(), GRID_RIGHT ) );
            }
            //If right is pressed
            if ( keystates[ SDLK_RIGHT ] ) {
                pc->set_grid ( process_grid_map ( grid_map, pc->get_current_grid(), GRID_RIGHT ) );
                pc_mirror->set_grid ( process_grid_map ( grid_map, pc_mirror->get_current_grid(), GRID_LEFT ) );
            }
            if ( event.type == SDL_QUIT ) {
                printf ( "%s %d Quit event decected.\n", __PRETTY_FUNCTION__, __LINE__ );
                quit = true;
            }
        }

        // Display on screen data
        stringstream osd_str;
        osd_str << "count" << counter;
        std::string boo = osd_str.str();
        const char * whoa = boo.c_str();

        osd = TTF_RenderText_Solid ( osd_font, whoa, osd_text_colour );
        if ( osd == NULL ) {
            printf ( "%s %d ERROR: Unable to load osd.\n", __PRETTY_FUNCTION__, __LINE__ );
            return 1;
        }
        SDL_Rect osd_location = {0, 0, 300, 100};


        // Fills background colour
        Uint32 bg_colour = SDL_MapRGB ( screen->format, 0, 255, 255 );
        if ( SDL_FillRect ( screen, &screen->clip_rect, bg_colour ) == -1 ) {
            printf ( "%s %d ERROR: failed to fill background colour.\n", __PRETTY_FUNCTION__, __LINE__ );
            return 1;
        }

        // Populate
        for ( int i = 0; i < grid_total; i++ ) {
            SDL_Rect gu_location = { gu_array[i]->get_x(),
                                     gu_array[i]->get_y(),
                                     gu_array[i]->get_w(),
                                     gu_array[i]->get_h()
                                   };
            gu_array[i]->get_y();
            gu_array[i]->get_w();
            gu_array[i]->get_h();

            SDL_Surface * gu_surface = gu_array[i]->get_surface();
            if ( gu_surface == NULL ) {
                printf ( "%s %d ERROR: failed to get gu_surface .\n", __PRETTY_FUNCTION__, __LINE__ );
                return 1;
            }
            SDL_BlitSurface ( gu_surface, NULL, screen, &gu_location );
        }

//        SDL_Rect pc_location = { pc->get_x(), pc->get_y(), pc->get_w(), pc->get_h() };
        SDL_Rect pc_location = get_pc_location ( gu_array[pc->get_current_grid()]->get_x(),
                               gu_array[pc->get_current_grid()]->get_y(),
                               gu_array[pc->get_current_grid()]->get_w(),
                               gu_array[pc->get_current_grid()]->get_h(),
                               pc->get_w(),
                               pc->get_h() );
        SDL_BlitSurface ( pc_surface, NULL, screen, &pc_location );
        
        SDL_Rect pc_mirron_location = get_pc_location ( gu_array[pc_mirror->get_current_grid()]->get_x(),
                               gu_array[pc_mirror->get_current_grid()]->get_y(),
                               gu_array[pc_mirror->get_current_grid()]->get_w(),
                               gu_array[pc_mirror->get_current_grid()]->get_h(),
                               pc_mirror->get_w(),
                               pc_mirror->get_h() );
        SDL_BlitSurface ( pc_mirror_surface, NULL, screen, &pc_mirron_location );
        
        SDL_BlitSurface ( osd, NULL, screen, &osd_location );

        if ( SDL_Flip ( screen ) == -1 ) {
            printf ( "%s %d ERROR: failed to flip.\n", __PRETTY_FUNCTION__, __LINE__ );
            return 1;
        }

        counter++;
        SDL_Delay ( 10 );
    }

    /* clean up */
    for ( int i = 0; i < grid_total; i++ ) {
        delete gu_array[i];
    }
    delete gu_array;
    delete pc;
    TTF_CloseFont ( osd_font );
    SDL_FreeSurface ( screen );
    SDL_Quit();

    return 0;
}
