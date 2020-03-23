//
// Created by erikberter on 15/03/2020.
//

#ifndef TEMPGAMEMOTOR_COLLISION_COMPONENT_H
#define TEMPGAMEMOTOR_COLLISION_COMPONENT_H


#include <SDL.h>
#include <ECS/ECS.h>
#include "transform_component.h"


class Collision_component : public Component {

private:

    std::string tag;
    Transform_component* transf;
public:
    SDL_Rect coll;
    Collision_component() : tag{""}{
        transf = nullptr;
    }
    Collision_component(std::string tag_t) : tag{std::move(tag_t)}{
        transf = nullptr;
    }

    void init() override{
        if(!entity->has_component<Transform_component>())
            entity->add_component<Transform_component>();
        transf = &entity->get_component<Transform_component>();
    }

    void update() override{
        coll.x = static_cast<int>(transf->x());
        coll.y = static_cast<int>(transf->y());
        coll.w = transf->width*transf->scale;
        coll.h = transf->height*transf->scale;
    }


};

#endif //TEMPGAMEMOTOR_COLLISION_COMPONENT_H
