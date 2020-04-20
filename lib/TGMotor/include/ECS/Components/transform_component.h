//
// Created by whiwho on 15/03/2020.
//

#ifndef TEMPGAMEMOTOR_TRANSFORM_COMPONENT_H
#define TEMPGAMEMOTOR_TRANSFORM_COMPONENT_H

#include "ECS/ECS.h"
#include "vector2d.h"

namespace ComponentHelper {
    extern ComponentHelper::ComponentType TRANSFORM;
}
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

    void set_data(json *data) override{
        if(data->contains("pos")){
            if((*data)["pos"].contains("x") && (*data)["pos"].contains("y"))
                pos = {(*data)["pos"]["x"], (*data)["pos"]["y"]};
            else pos.Zero();
        }else pos.Zero();

        if(data->contains("dims")){
            if((*data)["dims"].contains("h") && (*data)["dims"].contains("w")){
                height = (*data)["dims"]["h"];width = (*data)["dims"]["w"];
            }else height = width = 32;
        }else height = width = 32;

        if(data->contains("scale")) scale = (*data)["scale"];
        else scale = 1;

        if(data->contains("vel")){
            if((*data)["vel"].contains("x") && (*data)["vel"].contains("y"))
                vel = {(*data)["vel"]["x"],(*data)["vel"]["y"]};
            else vel.Zero();
        }else vel.Zero();
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
