#include <SDL.h>
#include <iostream>

class GridUnit {
	public:
		GridUnit(int x=0, int y=0, int w=60, int h=60);
		~GridUnit();
		SDL_Surface * get_surface();
		int get_x();
		int get_y();
		int get_w();
		int get_h();
		void set_x(int x);
		void set_y(int y);
		void set_w(int w);
		void set_h(int h);
	private:
		SDL_Surface *surface;
		int x;
		int y;
		int w;
		int h;
};