//
// Created by whiwho on 15/03/2020.
//

#ifndef TEMPGAMEMOTOR_COLLISION_H
#define TEMPGAMEMOTOR_COLLISION_H

#include "SDL.h"

class CollisionComponent;

class Collision{
public:
    static bool is_collision(SDL_Rect r1, SDL_Rect r2);
    static bool is_collision(const CollisionComponent& colA, const CollisionComponent& colB);
};

#endif //TEMPGAMEMOTOR_COLLISION_H
