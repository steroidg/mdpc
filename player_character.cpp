#include "player_character.hpp"

PlayerCharacter::PlayerCharacter(int w, int h)
{
	pc_x = 0;
	pc_y = 0;
	pc_w = w;
	pc_h = h;
	
	printf ("%s %d %d %d wee!.\n", __PRETTY_FUNCTION__, __LINE__, pc_h, pc_w);
}

PlayerCharacter::~PlayerCharacter()
{

}

int PlayerCharacter::get_x() {
	return pc_x;
}

int PlayerCharacter::get_y() {
	return pc_y;
}

int PlayerCharacter::get_w() {
	return pc_w;
}

int PlayerCharacter::get_h() {
	return pc_h;
}
