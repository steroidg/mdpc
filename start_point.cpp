#include "start_point.hpp"

StartPoint::StartPoint ( int x, int y, int w, int h, int grid ) {
    surface = NULL;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->current_grid = grid;

    surface = SDL_CreateRGBSurface ( 0, w, h, 32, 0, 0, 0, 0 );
    if ( surface == NULL ) {
        printf ( "%s %d ERROR: failed create surface.\n", __PRETTY_FUNCTION__, __LINE__ );
    }
    
    Uint32 colour = SDL_MapRGB ( surface->format, 100, 0, 100 );
    if ( SDL_FillRect ( surface, &surface->clip_rect , colour ) == -1 ) {
        printf ( "%s %d ERROR: failed to fill start_point colour.\n", __PRETTY_FUNCTION__, __LINE__ );
    }
}

StartPoint::~StartPoint() {
    SDL_FreeSurface ( surface );
}

SDL_Surface* StartPoint::get_surface() {
    return surface;
}

int StartPoint::get_x() {
    return x;
}

int StartPoint::get_y() {
    return y;
}

int StartPoint::get_w() {
    return w;
}

int StartPoint::get_h() {
    return h;
}

int StartPoint::get_current_grid() {
    return current_grid;
}

void StartPoint::set_x ( int x ) {
    this->x = x;
}

void StartPoint::set_y ( int y ) {
    this->y = y;
}

void StartPoint::set_w ( int w ) {
    this->w = w;
}

void StartPoint::set_h ( int h ) {
    this->h = h;
}

void StartPoint::set_grid ( int grid ) {
    this->current_grid = grid;
}