#ifndef MDPC_H
#define MDPC_H

// This header file should include everything that's shared across all objects
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <tr1/memory>
//#include <boost/shared_ptr.hpp>
using namespace std;

struct Dimension2D {
    int w;
    int h;
};

struct Position2D {
    int x;
    int y;
};

struct RGB_colour {
    int r;
    int g;
    int b;
};

#endif