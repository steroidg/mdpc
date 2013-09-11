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
		void set_x(int x);
		void set_y(int y);
		void set_w(int w);
		void set_h(int h);
		void set_colour (int r, int g, int b);
	private:
		SDL_Surface *surface;
		int x;
		int y;
		int w;
		int h;
		void render(int r, int g, int b);
};