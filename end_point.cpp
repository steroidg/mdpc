#include "end_point.hpp"

EndPoint::EndPoint ( int x, int y, int w, int h, int grid ) {
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
    
    Uint32 colour = SDL_MapRGB ( surface->format, 0, 100, 100 );
    if ( SDL_FillRect ( surface, &surface->clip_rect , colour ) == -1 ) {
        printf ( "%s %d ERROR: failed to fill start_point colour.\n", __PRETTY_FUNCTION__, __LINE__ );
    }
}

EndPoint::~EndPoint() {
    SDL_FreeSurface ( surface );
}

SDL_Surface* EndPoint::get_surface() {
    return surface;
}

int EndPoint::get_x() {
    return x;
}

int EndPoint::get_y() {
    return y;
}

int EndPoint::get_w() {
    return w;
}

int EndPoint::get_h() {
    return h;
}

int EndPoint::get_current_grid() {
    return current_grid;
}

void EndPoint::set_x ( int x ) {
    this->x = x;
}

void EndPoint::set_y ( int y ) {
    this->y = y;
}

void EndPoint::set_w ( int w ) {
    this->w = w;
}

void EndPoint::set_h ( int h ) {
    this->h = h;
}

void EndPoint::set_grid ( int grid ) {
    this->current_grid = grid;
}