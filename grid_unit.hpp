#include <SDL.h>
#include <iostream>

class GridUnit {
	public:
		GridUnit(int x, int y, int w, int h);
		~GridUnit();
		SDL_Surface * get_surface();
		int get_x();
		int get_y();
		int get_w();
		int get_h();
	private:
		SDL_Surface *surface;
		int x;
		int y;
		int w;
		int h;
};