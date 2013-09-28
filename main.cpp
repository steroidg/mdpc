#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include "player_character.hpp"
#include "start_point.hpp"
#include "end_point.hpp"
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
                //cout << "grid_map[" <<j << "][" << i << "] = " << grid_map[j][i] << '\n';
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
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 800;
    const int SCREEN_BPP = 32;
    const int GRID_SIZE_W = 50;
    const int GRID_SIZE_H = 50;
    const int PC_SIZE_W = 40;
    const int PC_SIZE_H = 40;
    const int SP_SIZE_W = 40;
    const int SP_SIZE_H = 40;
    bool quit = false;
    SDL_Event event;
    SDL_Surface *screen = NULL;
    SDL_Surface *osd = NULL;
    SDL_Surface *win_msg = NULL;
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
    osd_font = TTF_OpenFont ( "/home/billy/Dropbox/devel/mdpc/fonts/ubuntu/Ubuntu-B.ttf", 14 );
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

    PlayerCharacter * pc = new PlayerCharacter ( 0, 0, PC_SIZE_W, PC_SIZE_H, (rand() % grid_total) );
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

    StartPoint * sp = new StartPoint ( 0, 0, SP_SIZE_W, SP_SIZE_H, 45 );
    SDL_Surface * sp_surface = sp->get_surface();
    if ( sp_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load sp_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }
    
    EndPoint * ep = new EndPoint ( 0, 0, SP_SIZE_W, SP_SIZE_H, 99 );
    SDL_Surface * ep_surface = ep->get_surface();
    if ( ep_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load ep_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }

    StartPoint * pc_mirror_sp = new StartPoint ( 0, 0, SP_SIZE_W, SP_SIZE_H, 108 );
    SDL_Surface * pc_mirror_sp_surface = pc_mirror_sp->get_surface();
    if ( pc_mirror_sp_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load pc_mirror_sp_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }
    
    EndPoint * pc_mirror_ep = new EndPoint ( 0, 0, SP_SIZE_W, SP_SIZE_H, 120 );
    SDL_Surface * pc_mirror_ep_surface = pc_mirror_ep->get_surface();
    if ( pc_mirror_ep_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load pc_mirror_ep_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }
    
    srand (time(0));
    int pc_start = rand() % grid_total;
    int pc_mirror_start = pc_start;
    while ( pc_mirror_start == pc_start ) {
        pc_mirror_start = rand() %grid_total;
    cout << "pc_start = " << pc_start << endl;
    cout << "pc_mirror_start = " << pc_mirror_start << endl;
    }
    
    pc->set_grid(pc_start);
    pc_mirror->set_grid(pc_mirror_start);
    sp->set_grid(pc_start);
    pc_mirror_sp->set_grid(pc_mirror_start);
    
    int pc_end = pc_start;
    int pc_mirror_end = pc_mirror_start;
    int nmoves = rand() % 100 + 50;
    cout << "nmoves = " << nmoves << endl;
    
    for (int i = 0; i < nmoves; i++) {
        int move_direction = rand() %4 + 1;
        int pc_end_tmp = pc_end;
        int pc_mirror_end_tmp = pc_mirror_end;
        
        if ( move_direction == GRID_UP ) {
            pc_end_tmp = ( process_grid_map ( grid_map, pc_end, GRID_UP ) );
            pc_mirror_end_tmp = ( process_grid_map ( grid_map, pc_mirror_end, GRID_DOWN ) );
        } else if ( move_direction == GRID_DOWN ) {
            pc_end_tmp = ( process_grid_map ( grid_map, pc_end, GRID_DOWN ) );
            pc_mirror_end_tmp = ( process_grid_map ( grid_map, pc_mirror_end, GRID_UP ) );
        } else if ( move_direction == GRID_LEFT ) {
            pc_end_tmp = ( process_grid_map ( grid_map, pc_end, GRID_LEFT ) );
            pc_mirror_end_tmp = ( process_grid_map ( grid_map, pc_mirror_end, GRID_RIGHT ) );
        } else if ( move_direction == GRID_RIGHT ) {
            pc_end_tmp = ( process_grid_map ( grid_map, pc_end, GRID_RIGHT ) );
            pc_mirror_end_tmp = ( process_grid_map ( grid_map, pc_mirror_end, GRID_LEFT ) );
        }
        
        if (( pc_end != pc_end_tmp) && (pc_mirror_end != pc_mirror_end_tmp)) {
            pc_end = pc_end_tmp;
            pc_mirror_end = pc_mirror_end_tmp;
        }
        cout << move_direction << endl;
        cout << pc_end << endl;
        cout << pc_mirror_end << endl;
    }
    
    ep->set_grid(pc_end);
    pc_mirror_ep->set_grid(pc_mirror_end);
    
    
    win_msg = TTF_RenderText_Solid ( osd_font, "You a winrar!", osd_text_colour );
    SDL_Rect win_msg_location = {100, 100, 300, 200};

    /* game loop */
    int counter= 0;
    int pc_grid = 0;
    int pc_mirror_grid = 0;
    int pc_tmp_grid = 0;
    int pc_mirror_tmp_grid = 0;
    while ( quit == false ) {
        // Event handler
        pc_grid = pc->get_current_grid();
        pc_tmp_grid = pc->get_current_grid();
        pc_mirror_grid = pc_mirror->get_current_grid();
        pc_mirror_tmp_grid = pc_mirror->get_current_grid();
        while ( SDL_PollEvent ( &event ) ) {
            Uint8 *keystates = SDL_GetKeyState ( NULL );
            if ( keystates[ SDLK_UP ] ) {
                pc_tmp_grid = ( process_grid_map ( grid_map, pc->get_current_grid(), GRID_UP ) );
                pc_mirror_tmp_grid = ( process_grid_map ( grid_map, pc_mirror->get_current_grid(), GRID_DOWN ) );
            }
            //If down is pressed
            if ( keystates[ SDLK_DOWN ] ) {
                pc_tmp_grid = ( process_grid_map ( grid_map, pc->get_current_grid(), GRID_DOWN ) );
                pc_mirror_tmp_grid = ( process_grid_map ( grid_map, pc_mirror->get_current_grid(), GRID_UP ) );
            }
            //If left is pressed
            if ( keystates[ SDLK_LEFT ] ) {
                pc_tmp_grid = ( process_grid_map ( grid_map, pc->get_current_grid(), GRID_LEFT ) );
                pc_mirror_tmp_grid = ( process_grid_map ( grid_map, pc_mirror->get_current_grid(), GRID_RIGHT ) );
            }
            //If right is pressed
            if ( keystates[ SDLK_RIGHT ] ) {
                pc_tmp_grid = ( process_grid_map ( grid_map, pc->get_current_grid(), GRID_RIGHT ) );
                pc_mirror_tmp_grid = ( process_grid_map ( grid_map, pc_mirror->get_current_grid(), GRID_LEFT ) );
            }
            if ( event.type == SDL_QUIT ) {
                printf ( "%s %d Quit event decected.\n", __PRETTY_FUNCTION__, __LINE__ );
                quit = true;
            }
        }

            if (( pc_grid != pc_tmp_grid) && (pc_mirror_grid != pc_mirror_tmp_grid)) {
                pc->set_grid(pc_tmp_grid);
                pc_mirror->set_grid(pc_mirror_tmp_grid);
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

        SDL_Rect sp_location = get_pc_location ( gu_array[sp->get_current_grid()]->get_x(),
                               gu_array[sp->get_current_grid()]->get_y(),
                               gu_array[sp->get_current_grid()]->get_w(),
                               gu_array[sp->get_current_grid()]->get_h(),
                               sp->get_w(),
                               sp->get_h() );
        SDL_BlitSurface ( sp_surface, NULL, screen, &sp_location );
        
        SDL_Rect ep_location = get_pc_location ( gu_array[ep->get_current_grid()]->get_x(),
                               gu_array[ep->get_current_grid()]->get_y(),
                               gu_array[ep->get_current_grid()]->get_w(),
                               gu_array[ep->get_current_grid()]->get_h(),
                               ep->get_w(),
                               ep->get_h() );
        SDL_BlitSurface ( ep_surface, NULL, screen, &ep_location );
        
        SDL_Rect pc_mirror_sp_location = get_pc_location ( gu_array[pc_mirror_sp->get_current_grid()]->get_x(),
                               gu_array[pc_mirror_sp->get_current_grid()]->get_y(),
                               gu_array[pc_mirror_sp->get_current_grid()]->get_w(),
                               gu_array[pc_mirror_sp->get_current_grid()]->get_h(),
                               pc_mirror_sp->get_w(),
                               pc_mirror_sp->get_h() );
        SDL_BlitSurface ( pc_mirror_sp_surface, NULL, screen, &pc_mirror_sp_location );
        
        SDL_Rect pc_mirror_ep_location = get_pc_location ( gu_array[pc_mirror_ep->get_current_grid()]->get_x(),
                               gu_array[pc_mirror_ep->get_current_grid()]->get_y(),
                               gu_array[pc_mirror_ep->get_current_grid()]->get_w(),
                               gu_array[pc_mirror_ep->get_current_grid()]->get_h(),
                               pc_mirror_ep->get_w(),
                               pc_mirror_ep->get_h() );
        SDL_BlitSurface ( pc_mirror_ep_surface, NULL, screen, &pc_mirror_ep_location );


        if ( pc_mirror->get_current_grid() == pc_mirror_ep->get_current_grid() ) {
            SDL_BlitSurface ( win_msg, NULL, screen, &win_msg_location );
        }
        
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
    delete pc_mirror;
    delete sp;
    delete ep;
    TTF_CloseFont ( osd_font );
    SDL_FreeSurface ( screen );
    SDL_Quit();

    return 0;
}
