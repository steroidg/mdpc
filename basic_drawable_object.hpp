#ifndef BASIC_DRAWABLE_OBJECT_H
#define BASIC_DRAWABLE_OBJECT_H
#include "mdpc.hpp"

class BasicDrawableObject
{
public:
    /**
     * Constructor
     * \param p Position of the object
     * \param d Dimension of the object
     * \param bpp bits per pixel for the SDL_Surface
     */
    BasicDrawableObject ( Position2D p, Dimension2D d, int bpp );
    /** Destructor */
    ~BasicDrawableObject ();
    SDL_Surface * get_surface ();
    Position2D get_position ();
    Dimension2D get_dimension ();
    void set_x ( int x );
    void set_y ( int y );
    void set_w ( int w );
    void set_h ( int h );

protected:
    SDL_Surface * surface;
    Position2D position;
    Dimension2D dimension;
    int bpp;
};

#endif