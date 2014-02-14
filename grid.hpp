#ifndef GRID_H
#define GRID_H
#include "mdpc.hpp"
#include "grid_unit.hpp"

class Grid
{
    public:
        /**
         * Constructor
         * \param screen_x screen resolution x axis
         * \param screen_y screen resolution y axis
         * \param bpp bits per pixel for all SDL surfaces
         */
        Grid ( int screen_x, int screen_y, int bpp );
        /** Destructor */
        ~Grid ();
        
        /** Obtain the grid map matrix */
        vector< vector< int > > get_grid_map ();
        /** Obtain the grid unit array */
        vector< GridUnit * > get_gu_array ();
        /** Obtain the dimension of a grid */
        Dimension2D get_grid_dimension ();
        
    private:
        /** grid map matrix */
        vector< vector<int> > grid_map;
        /** grid unit array */
        vector< GridUnit * > gu_array;
        /** dimension of a grid */
        Dimension2D grid_dimension;
};
#endif