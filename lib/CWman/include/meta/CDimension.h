#ifndef WINDOW_MANAGER_CDIMENSION_H
#define WINDOW_MANAGER_CDIMENSION_H

#include <SDL_rect.h>

struct Position{
    int x, y;
};

struct Dimension{
    int w, h;
};

extern SDL_Rect d_to_R(Position p, Dimension d);

#endif //WINDOW_MANAGER_CDIMENSION_H
