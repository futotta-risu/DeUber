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
    Car_component(){

    }

    void init() override{
        if(!entity->has_component(ComponentHelper::TRANSFORM))
            entity->add_component(ComponentHelper::TRANSFORM);
        transf = dynamic_cast<TransformComponent*>(entity->get_component(ComponentHelper::TRANSFORM));
        transf->pos.x = 0;
        transf->pos.y = 0;
        transf->speed=1;
    }

    void update() override{

        if(counter%15==0)
            alg->move_car(mapa, act_car);

        counter ++;
        int dir = act_car->dir;

        transf->vel.y = (2*(dir%2)-((dir*dir*dir)%4));
        transf->vel.x = (((dir+1)%2==0 || dir==0) ? 0: ((dir == 2) ? 1 : -1));

    }
    void set_case(car* act_car_t, generic_algorithm* alg_t, Map* mapa_t){
        alg = alg_t;
        act_car = act_car_t;
        mapa = mapa_t;
        if(!entity->has_component(ComponentHelper::TRANSFORM))
            entity->add_component(ComponentHelper::TRANSFORM);
        transf = dynamic_cast<TransformComponent*>(entity->get_component(ComponentHelper::TRANSFORM));
        transf->pos.x = 32*act_car->get_coord_x();
        transf->pos.y = 32*act_car->get_coord_y();
        transf->speed=1;
    }


};

#endif //DEUBER_CAR_COMPONENT_H
