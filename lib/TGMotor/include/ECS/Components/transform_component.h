//
// Created by whiwho on 15/03/2020.
//

#ifndef TEMPGAMEMOTOR_TRANSFORM_COMPONENT_H
#define TEMPGAMEMOTOR_TRANSFORM_COMPONENT_H

#include "ECS/ECS.h"
#include "vector2d.h"

class TransformComponent : public Component{

public:
    Vector2D<float> pos;
    Vector2D<float> vel;

    int height = 32, width = 32;
    int scale = 1;

    float speed = 1;

    TransformComponent(){
        pos.Zero();
        vel.Zero();
    }

    TransformComponent(float x, float y){
        pos.x = x;
        pos.y = y;
        vel.Zero();
    }

    TransformComponent(float x, float y, int h, int w, int scale_t){
        pos.x = x;
        pos.y = y;
        height = h;
        width = w;
        scale = scale_t;
        vel.Zero();
    }

    float x(){return pos.x;}
    float y(){return pos.y;}

    void init() override{
        vel.Zero();
    }

    void update() override{
        pos.x += vel.x*speed;
        pos.y += vel.y*speed;
    }

    void set_pos(int x, int y){
        pos.x = x;
        pos.y = y;
    }
};

#endif //TEMPGAMEMOTOR_TRANSFORM_COMPONENT_H
