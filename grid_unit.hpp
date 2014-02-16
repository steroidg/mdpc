#ifndef GRID_UNIT_H
#define GRID_UNIT_H
#include "mdpc.hpp"
#include "basic_drawable_object.hpp"

class GridUnit: public BasicDrawableObject
{
    public:
        /** Constructory
         * \param p Position of the grid
         * \param d Dimension of the grid
         * \param bpp bits per pixel of the SDL_Surface object for the grid
         */
        GridUnit ( Position2D p, Dimension2D d, int bpp );
        /** Destructor */
        ~GridUnit ();
        /**
         * Set the colour of the grid
         * \param colour Colour to be set
         */ 
        void set_colour ( RGB_colour * colour );
        
    private:
        /** Colour of the grid */
        RGB_colour * colour;
        /** SDL surface pointe of the grid
        SDL_Surface * surface;
};
#endif
