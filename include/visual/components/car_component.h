//
// Created by erikberter on 19/03/2020.
//

#ifndef DEUBER_CAR_COMPONENT_H
#define DEUBER_CAR_COMPONENT_H

#include "maps/car.h"
#include "ECS/ECS.h"
#include <ECS/Components/transform_component.h>
#include "algorithms/generic_algorithm.h"
#include "maps/map.h"

#define CAR_SPEED 1

namespace ComponentHelper{
    extern ComponentHelper::ComponentType CARC;
}
class Car_component : public Component {

private:

    TransformComponent* transf;
    generic_algorithm* alg;
    car* act_car;
    Map* mapa;
    int counter = 0;
public:
    Car_component() = default;

    void init() override{
        transf = dynamic_cast<TransformComponent*>(entity->add_component(ComponentHelper::TRANSFORM));
        transf->pos = {0,0};
        transf->speed=1;
    }

    void update() override{
        if(++counter%(32/CAR_SPEED)==0)
            alg->move_car(mapa, act_car);
        set_vel_from_dir(act_car->dir);
    }

    void set_vel_from_dir(int dir){
        if(dir == 0) transf->vel = {0,0};
        else if(dir%2 == 0) transf->vel = {(dir==2)? 1.0f : -1.0f,0};
        else transf->vel =transf->vel = {0,(dir==1)? 1.0f : -1.0f};
    }
    void set_case(car* act_car_t, generic_algorithm* alg_t, Map* mapa_t){
        alg = alg_t;
        act_car = act_car_t;
        mapa = mapa_t;
        transf = dynamic_cast<TransformComponent*>(entity->add_component(ComponentHelper::TRANSFORM));
        transf->pos = Vector2D<float>(act_car->get_coord_x(),act_car->get_coord_y())* 32;
        transf->speed = CAR_SPEED;
    }


};

#endif //DEUBER_CAR_COMPONENT_H
