//
// Created by whiwho on 17/03/2020.
//

#ifndef TEMPGAMEMOTOR_RANDOM_MOVEMENT_COMPONENT_H
#define TEMPGAMEMOTOR_RANDOM_MOVEMENT_COMPONENT_H

#include <SDL.h>
#include "../ECS.h"
#include "transform_component.h"

class Random_component : public Component {

private:

    Transform_component* transf;
public:
    SDL_Rect coll;
    Random_component(){
    }

    void init() override{
        if(!entity->has_component<Transform_component>())
            entity->add_component<Transform_component>();
        transf = &entity->get_component<Transform_component>();

    }

    void update() override{
        transf->vel.x = (rand()%3)-1;
        transf->vel.y = (rand()%3)-1;
    }


};

#endif //TEMPGAMEMOTOR_RANDOM_MOVEMENT_COMPONENT_H
