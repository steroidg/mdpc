#include "mdpc.hpp"
#include "basic_drawable_object.hpp"
#include "grid_unit.hpp"
#include "grid.hpp"
#include "moveable_object.hpp"

#define GRID_UP 1
#define GRID_DOWN 2
#define GRID_LEFT 3
#define GRID_RIGHT 4

typedef boost::shared_ptr<GridUnit> grid_unit_ptr;
typedef boost::shared_ptr<MoveableObject> moveable_object_ptr;
typedef boost::shared_ptr<Grid> grid_ptr;

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
        if ( pc_centre_x >= gu_array[i]->get_position()->x &&
                pc_centre_x < ( gu_array[i]->get_position()->x + gu_array[i]->get_dimension()->w ) &&
                pc_centre_y >= gu_array[i]->get_position()->y &&
                pc_centre_y < ( gu_array[i]->get_position()->y + gu_array[i]->get_dimension()->h ) ) {
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
    int grid_y = grid_map.size();
    int grid_x = grid_map[0].size();
    int retval = 5;

    cout << "current_grid = " << current_grid << "\n" << endl;
    cout << "direction = " << direction << "\n" << endl;

    for ( int j=0; j<grid_y; j++ ) {
        for ( int i=0; i<grid_x; i++ ) {
            if ( current_grid == grid_map[j][i] ) {
                cout << "grid_map[" <<j << "][" << i << "] = " << grid_map[j][i] << '\n';
                switch ( direction ) {
                case GRID_UP:
                    if ( j > 0 ) {
                        retval = grid_map[j-1][i];
                    } else {
                        retval = current_grid;
                    }
                    break;
                case GRID_DOWN:
                    if ( j < ( grid_y-1 ) ) {
                        retval = grid_map[j+1][i];
                    } else {
                        retval = current_grid;
                    }
                    break;
                case GRID_LEFT:
                    if ( i > 0 ) {
                        retval = grid_map[j][i-1];
                    } else {
                        retval = current_grid;
                    }
                    break;
                case GRID_RIGHT:
                    if ( i < ( grid_x-1 ) ) {
                        retval = grid_map[j][i+1];
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


// This function initialize everything that doesn't need to return.
bool init ()
{
    if ( SDL_Init ( SDL_INIT_EVERYTHING ) < 0 ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: failed to init SDL."
             << endl;
        return false;
    };

    if ( TTF_Init() < 0 ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: failed to init TTF."
             << endl;
        return false;
    };

    return true;
}


SDL_Surface * init_game_screen ()
{
    const SDL_VideoInfo* vinfo = SDL_GetVideoInfo();
    const int screen_width = ( vinfo->current_w - 10 );
    const int screen_height = ( vinfo->current_h - 10 );
    const int screen_bpp = 32;

    SDL_Surface * screen = SDL_SetVideoMode ( screen_width, screen_height,
                           screen_bpp, SDL_HWSURFACE );
    return screen;
}

// Main function duh!
int main ( int argc, char * argv[] )
{
    if ( ! init() ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: failed to init."
             << endl;
        return 1;
    }

    SDL_Surface * game_screen_ptr = NULL;
    game_screen_ptr = init_game_screen ();
    if ( game_screen_ptr == NULL ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: Unable to init game screen."
             << endl;
        return 1;
    }

    // Base variables
    bool quit = false;
    SDL_Event event;

    // On screen display related variables.
    sdl_surface_ptr osd;
    sdl_surface_ptr win_msg;
    TTF_Font *osd_font = NULL;
    SDL_Color osd_text_colour = { 0, 255, 0 };
    osd_font = TTF_OpenFont ( "/home/billy/Dropbox/devel/mdpc/fonts/ubuntu/Ubuntu-B.ttf", 14 );
    if ( osd_font == NULL ) {
        cout << __PRETTY_FUNCTION__ << " "
             << __LINE__ << " "
             << "ERROR: Unable to load font.\n"
             << "ERROR: Unable to init game screen."
             << endl;
        return 1;
    }

    grid_ptr game_grid = grid_ptr ( new Grid ( game_screen_ptr->w,
                                    game_screen_ptr->h,
                                    game_screen_ptr->format->BitsPerPixel ) );

    vector< grid_unit_ptr > gu_array = game_grid->get_grid_units();
    vector< vector<int> > grid_map = game_grid->get_grid_map ();


    // Game related variables
    position_ptr starting_position (new Position);
    starting_position->x = 0;
    starting_position->y = 0;
    
    dimension_ptr character_dimension (new Dimension);
    character_dimension->w = game_grid->get_grid_width() / 4;
    character_dimension->h = game_grid->get_grid_width() / 4;
    
    dimension_ptr character_mirror_dimension (new Dimension);
    character_mirror_dimension->w = game_grid->get_grid_width() / 6;
    character_mirror_dimension->h = game_grid->get_grid_width() / 6;
    
    
    dimension_ptr start_point_dimension (new Dimension);
    start_point_dimension->w = game_grid->get_grid_width() / 2;
    start_point_dimension->h = game_grid->get_grid_width() / 2;
    
    dimension_ptr end_point_dimension (new Dimension);
    end_point_dimension->w = game_grid->get_grid_width() / 3;
    end_point_dimension->h = game_grid->get_grid_width() / 3;

    moveable_object_ptr pc = moveable_object_ptr ( new MoveableObject (
                             starting_position,
                             character_dimension,
                             game_screen_ptr->format->BitsPerPixel,
                             ( rand() % game_grid->get_grid_total() ) ) );
    sdl_surface_ptr pc_surface = pc->get_surface();
    if ( pc_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load pc_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }

    moveable_object_ptr pc_mirror = moveable_object_ptr ( new MoveableObject (
                                    starting_position,
                                    character_mirror_dimension,
                                    game_screen_ptr->format->BitsPerPixel, ( rand() %
                                            game_grid->get_grid_total() ) ) );
    sdl_surface_ptr pc_mirror_surface = pc_mirror->get_surface();
    if ( pc_mirror_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load pc_mirror_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }

    moveable_object_ptr sp = moveable_object_ptr ( new MoveableObject (
                             starting_position,
                             start_point_dimension,
                             game_screen_ptr->format->BitsPerPixel, 45 ) );
    sdl_surface_ptr sp_surface = sp->get_surface();
    if ( sp_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load sp_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }

    moveable_object_ptr ep = moveable_object_ptr ( new MoveableObject (
                             starting_position,
                             end_point_dimension,
                             game_screen_ptr->format->BitsPerPixel, 99 ) );
    sdl_surface_ptr ep_surface = ep->get_surface();
    if ( ep_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load ep_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }

    moveable_object_ptr pc_mirror_sp = moveable_object_ptr ( new MoveableObject (
                                       starting_position,
                                       start_point_dimension,
                                       game_screen_ptr->format->BitsPerPixel,
                                       108 ) );
    sdl_surface_ptr pc_mirror_sp_surface = pc_mirror_sp->get_surface();
    if ( pc_mirror_sp_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load pc_mirror_sp_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }

    moveable_object_ptr pc_mirror_ep = moveable_object_ptr ( new MoveableObject (
                                       starting_position,
                                       end_point_dimension,
                                       game_screen_ptr->format->BitsPerPixel,
                                       120 ) );
    sdl_surface_ptr pc_mirror_ep_surface = pc_mirror_ep->get_surface();
    if ( pc_mirror_ep_surface == NULL ) {
        printf ( "%s %d ERROR: Unable to load pc_mirror_ep_surface.\n", __PRETTY_FUNCTION__, __LINE__ );
        return 1;
    }

    srand ( time ( 0 ) );
    int pc_start = rand() % game_grid->get_grid_total();
    int pc_mirror_start = pc_start;
    while ( pc_mirror_start == pc_start ) {
        pc_mirror_start = rand() % game_grid->get_grid_total();
        cout << "pc_start = " << pc_start << endl;
        cout << "pc_mirror_start = " << pc_mirror_start << endl;
    }

    pc->set_grid ( pc_start );
    pc_mirror->set_grid ( pc_mirror_start );
    sp->set_grid ( pc_start );
    pc_mirror_sp->set_grid ( pc_mirror_start );

    int pc_end = pc_start;
    int pc_mirror_end = pc_mirror_start;
    int nmoves = rand() % 300 + 200;
    cout << "nmoves = " << nmoves << endl;

    for ( int i = 0; i < nmoves; i++ ) {
        // Generate random direction, which is #defined as from 1-4
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

        if ( ( pc_end != pc_end_tmp ) && ( pc_mirror_end != pc_mirror_end_tmp ) ) {
            pc_end = pc_end_tmp;
            pc_mirror_end = pc_mirror_end_tmp;
        }
//        cout << move_direction << endl;
//        cout << pc_end << endl;
//        cout << pc_mirror_end << endl;
    }

    ep->set_grid ( pc_end );
    pc_mirror_ep->set_grid ( pc_mirror_end );


    win_msg = sdl_surface_ptr ( TTF_RenderText_Solid ( osd_font, "You a winrar!", osd_text_colour ) );
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

        if ( ( pc_grid != pc_tmp_grid ) && ( pc_mirror_grid != pc_mirror_tmp_grid ) ) {
            pc->set_grid ( pc_tmp_grid );
            pc_mirror->set_grid ( pc_mirror_tmp_grid );
        }
        // Display on screen data
        stringstream osd_str;
        osd_str << "count" << counter;
        std::string boo = osd_str.str();
        const char * whoa = boo.c_str();

        osd = sdl_surface_ptr ( TTF_RenderText_Solid ( osd_font, whoa, osd_text_colour ) );
        if ( osd == NULL ) {
            printf ( "%s %d ERROR: Unable to load osd.\n", __PRETTY_FUNCTION__, __LINE__ );
            return 1;
        }
        SDL_Rect osd_location = {0, 0, 300, 100};


        // Fills background colour
        Uint32 bg_colour = SDL_MapRGB ( game_screen_ptr->format, 0, 255, 255 );
        if ( SDL_FillRect ( game_screen_ptr, &game_screen_ptr->clip_rect, bg_colour ) == -1 ) {
            printf ( "%s %d ERROR: failed to fill background colour.\n", __PRETTY_FUNCTION__, __LINE__ );
            return 1;
        }

        // Populate
        for ( int i = 0; i < game_grid->get_grid_total(); i++ ) {
            SDL_Rect gu_location = { gu_array[i]->get_position()->x,
                                     gu_array[i]->get_position()->y,
                                     gu_array[i]->get_dimension()->w,
                                     gu_array[i]->get_dimension()->h
                                   };
//            gu_array[i]->get_position()[1];
//            gu_array[i]->get_dimension()[0];
//            gu_array[i]->get_dimension()[1];

            sdl_surface_ptr gu_surface = gu_array[i]->get_surface();
            if ( gu_surface == NULL ) {
                printf ( "%s %d ERROR: failed to get gu_surface .\n", __PRETTY_FUNCTION__, __LINE__ );
                return 1;
            }
            SDL_BlitSurface ( & ( *gu_surface ), NULL, game_screen_ptr, &gu_location );
        }

//        SDL_Rect pc_location = { pc->get_x(), pc->get_y(), pc->get_w(), pc->get_h() };
        SDL_Rect pc_location = get_pc_location (
                               gu_array[pc->get_current_grid()]->get_position()->x,
                               gu_array[pc->get_current_grid()]->get_position()->y,
                               gu_array[pc->get_current_grid()]->get_dimension()->w,
                               gu_array[pc->get_current_grid()]->get_dimension()->h,
                               pc->get_dimension()->w,
                               pc->get_dimension()->h );
        SDL_BlitSurface ( & ( *pc_surface ), NULL, game_screen_ptr, &pc_location );

        SDL_Rect pc_mirron_location = get_pc_location (
                                      gu_array[pc_mirror->get_current_grid()]->get_position()->x,
                                      gu_array[pc_mirror->get_current_grid()]->get_position()->y,
                                      gu_array[pc_mirror->get_current_grid()]->get_dimension()->w,
                                      gu_array[pc_mirror->get_current_grid()]->get_dimension()->h,
                                      pc_mirror->get_dimension()->w,
                                      pc_mirror->get_dimension()->h );
        SDL_BlitSurface ( & ( *pc_mirror_surface ), NULL, game_screen_ptr, &pc_mirron_location );

        SDL_Rect sp_location = get_pc_location (
                               gu_array[sp->get_current_grid()]->get_position()->x,
                               gu_array[sp->get_current_grid()]->get_position()->y,
                               gu_array[sp->get_current_grid()]->get_dimension()->w,
                               gu_array[sp->get_current_grid()]->get_dimension()->h,
                               sp->get_dimension()->w,
                               sp->get_dimension()->h );
        SDL_BlitSurface ( & ( *sp_surface ), NULL, game_screen_ptr, &sp_location );

        SDL_Rect ep_location = get_pc_location (
                               gu_array[ep->get_current_grid()]->get_position()->x,
                               gu_array[ep->get_current_grid()]->get_position()->y,
                               gu_array[ep->get_current_grid()]->get_dimension()->w,
                               gu_array[ep->get_current_grid()]->get_dimension()->h,
                               ep->get_dimension()->w,
                               ep->get_dimension()->h );
        //SDL_BlitSurface ( ep_surface, NULL, screen, &ep_location );

        SDL_Rect pc_mirror_sp_location = get_pc_location (
                                         gu_array[pc_mirror_sp->get_current_grid()]->get_position()->x,
                                         gu_array[pc_mirror_sp->get_current_grid()]->get_position()->y,
                                         gu_array[pc_mirror_sp->get_current_grid()]->get_dimension()->w,
                                         gu_array[pc_mirror_sp->get_current_grid()]->get_dimension()->h,
                                         pc_mirror_sp->get_dimension()->w,
                                         pc_mirror_sp->get_dimension()->h );
        SDL_BlitSurface ( & ( *pc_mirror_sp_surface ), NULL, game_screen_ptr, &pc_mirror_sp_location );

        SDL_Rect pc_mirror_ep_location = get_pc_location (
                                         gu_array[pc_mirror_ep->get_current_grid()]->get_position()->x,
                                         gu_array[pc_mirror_ep->get_current_grid()]->get_position()->y,
                                         gu_array[pc_mirror_ep->get_current_grid()]->get_dimension()->w,
                                         gu_array[pc_mirror_ep->get_current_grid()]->get_dimension()->h,
                                         pc_mirror_ep->get_dimension()->w,
                                         pc_mirror_ep->get_dimension()->h);
        SDL_BlitSurface ( & ( *pc_mirror_ep_surface ), NULL, game_screen_ptr, &pc_mirror_ep_location );


        if ( pc_mirror->get_current_grid() == pc_mirror_ep->get_current_grid() ) {
            SDL_BlitSurface ( & ( *win_msg ), NULL, game_screen_ptr, &win_msg_location );
        }

        SDL_BlitSurface ( & ( *osd ), NULL, game_screen_ptr, &osd_location );

        if ( SDL_Flip ( game_screen_ptr ) == -1 ) {
            printf ( "%s %d ERROR: failed to flip.\n", __PRETTY_FUNCTION__, __LINE__ );
            return 1;
        }

        counter++;
        SDL_Delay ( 10 );
    }

    TTF_CloseFont ( osd_font );
    SDL_FreeSurface ( game_screen_ptr );
    SDL_Quit();

    return 0;
}
