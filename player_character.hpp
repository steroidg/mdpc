#include <SDL.h>
#include <iostream>

class PlayerCharacter {
	public:
		PlayerCharacter(int w, int h);
		~PlayerCharacter();
		int get_x();
		int get_y();
		int get_w();
		int get_h();
	private:
//		SDL_Surface *pc_surface;
		int pc_x;
		int pc_y;
		int pc_w;
		int pc_h;
};