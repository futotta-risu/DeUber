//
// Created by erikberter on 18/03/2020.
//

#ifndef DEUBER_CAR_ENTITY_H
#define DEUBER_CAR_ENTITY_H

#include <game_component.h>
#include "visual/components/car_component.h"
#include "visual/visual_run_handler.h"
#include "ECS/components/components.h"
#include "ECS/components/random_movement_component.h"

class car_entity{
public:
    static void add_player(std::string id, GameApp* gApp,  car* act_car, generic_algorithm* alg_t, Map* mapa) {
        auto& player = gApp->add_entity();
        player.add_component<Transform_component>(64*act_car->get_coord_x(),64*act_car->get_coord_y());
        player.add_component<Sprite_component>(id, gApp, true);
        // TODO arreglar el tema ID's
        player.add_component<Collision_component>(id);
        player.add_component<Car_component>(act_car, alg_t, mapa);
        player.add_group(2);
    }

};

#endif //DEUBER_CAR_ENTITY_H
