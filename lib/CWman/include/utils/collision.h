//
// Created by whiwho on 25/03/2020.
//

#ifndef WINDOW_MANAGER_COLLISION_H
#define WINDOW_MANAGER_COLLISION_H

#include <SDL_rect.h>

static bool is_inside_rect(SDL_Rect* coords, int x, int y){
    if(coords->x < x && coords->x + coords->w > x && coords->y < y && coords->y + coords->h > y)
        return true;
    return false;
}

#endif //WINDOW_MANAGER_COLLISION_H
