//
// Created by whiwho on 18/03/2020.
//

#ifndef DEUBER_CAR_ENTITY_H
#define DEUBER_CAR_ENTITY_H

#include "../Components/car_component.h"
#include "../../visual_run_handler.h"
#include "../Components/components.h"
#include "../Components/random_movement_component.h"

class car_entity{
public:
    static void add_player(std::string id) {
        auto& player(visual_run_handler::ent_man.man.add_entity());
        player.add_component<Transform_component>();
        player.add_component<Sprite_component>(id, true);
        // TODO arreglar el tema ID's
        player.add_component<Collision_component>(id);

        player.add_group(G_CAR);
    }

    static void add_player(std::string id, car* act_car) {
            auto& player(visual_run_handler::ent_man.man.add_entity());
            player.add_component<Transform_component>(64*act_car->get_coord_x(),64*act_car->get_coord_y());
            player.add_component<Sprite_component>(id, true);
            // TODO arreglar el tema ID's
            player.add_component<Collision_component>(id);
            player.add_component<Car_component>(act_car);
            player.add_group(G_CAR);
    }

};

#endif //DEUBER_CAR_ENTITY_H
