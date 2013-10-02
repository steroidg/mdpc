#include "basic_drawable_object.hpp"

class PlayerCharacter: public BasicDrawableObject
{
public:
    PlayerCharacter ( int x, int y, int w, int h, int bpp, int grid );
    ~PlayerCharacter();
    int get_current_grid();
    void set_grid ( int grid );
private:
    int current_grid;
};
