//
// Created by erikberter on 19/03/2020.
//

#ifndef DEUBER_CAR_COMPONENT_H
#define DEUBER_CAR_COMPONENT_H

#include "maps/car.h"
#include "ECS/ECS.h"
#include "ECS/components/transform_component.h"

class Car_component : public Component {

private:

    TransformComponent* transf;
    generic_algorithm* alg;
    car* act_car;
    Map* mapa;
    int counter = 0;
public:
    Car_component(car* act_car_t, generic_algorithm* alg_t, Map* mapa_t){
        alg = alg_t;
        act_car = act_car_t;
        mapa = mapa_t;
    }

    void init() override{
        if(!entity->has_component<TransformComponent>())
            entity->add_component<TransformComponent>();
        transf = &entity->get_component<TransformComponent>();
        transf->pos.x = 50*act_car->get_coord_x();
        transf->pos.y = 50*act_car->get_coord_y();
        transf->speed=3.5;
    }

    void update() override{

        if(counter%15==0)
            alg->move_car(mapa, act_car);

        counter ++;
        int dir = act_car->dir;

        transf->vel.y = (2*(dir%2)-((dir*dir*dir)%4));
        transf->vel.x = (((dir+1)%2==0 || dir==0) ? 0: ((dir == 2) ? 1 : -1));
    }


};

#endif //DEUBER_CAR_COMPONENT_H
