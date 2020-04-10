//
// Created by erikberter on 18/03/2020.
//

#ifndef DEUBER_CAR_ENTITY_H
#define DEUBER_CAR_ENTITY_H

#include "ECS/Components/collision_component.h"
#include "visual/game_component.h"
#include "visual/components/car_component.h"
#include "visual/visual_run_handler.h"

#include "ECS/Components/sprite_component.h"
#include "ECS/Components/transform_component.h"


class car_entity{
public:
    static void add_player(std::string id, Game* gApp,  car* act_car, generic_algorithm* alg_t, Map* mapa) {
        auto& player = gApp->e_man.man.add_entity();
        player.add_component<TransformComponent>(50*act_car->get_coord_x(),50*act_car->get_coord_y());
        player.add_component<SpriteComponent>(id, gApp, true);
        // TODO arreglar el tema ID's
        player.add_component<CollisionComponent>(gApp);
        player.add_component<Car_component>(act_car, alg_t, mapa);
        player.add_group(2);
    }

};

#endif //DEUBER_CAR_ENTITY_H
