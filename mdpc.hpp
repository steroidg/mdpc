#ifndef MDPC_H
#define MDPC_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <tr1/memory>
#include <boost/shared_ptr.hpp>
using namespace std;

struct Position {
    int x;
    int y;
};

struct Dimension {
    int w;
    int h;
};

typedef boost::shared_ptr<SDL_Surface> sdl_surface_ptr;
typedef boost::shared_ptr<Position> position_ptr;
typedef boost::shared_ptr<Dimension> dimension_ptr;
#endif