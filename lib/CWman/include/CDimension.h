//
// Created by whiwho on 24/03/2020.
//

#ifndef WINDOW_MANAGER_CDIMENSION_H
#define WINDOW_MANAGER_CDIMENSION_H

#include <SDL_rect.h>

struct Position{
    int x, y;
};

struct Dimension{
    int w, h;
};


static SDL_Rect d_to_R(Position p, Dimension d){
    SDL_Rect a = {p.x,p.y,d.w,d.h};
    return a;
}

#endif //WINDOW_MANAGER_CDIMENSION_H
