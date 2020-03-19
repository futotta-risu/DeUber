//
// Created by whiwho on 19/03/2020.
//

#ifndef DEUBER_GOAL_ENTITY_H
#define DEUBER_GOAL_ENTITY_H

#include "../../visual_run_handler.h"
#include "../Components/components.h"
#include "../Components/random_movement_component.h"

#include <goal.h>
#include <visual/ECS/Components/goal_component.h>

class goal_entity{
public:

    static void add_goal(std::string id, Goal* goal_t, int y, int x) {
        auto& player(visual_run_handler::ent_man.man.add_entity());
        player.add_component<Transform_component>(x*64,y*64);
        player.add_component<Goal_component>(goal_t);
        player.add_component<Sprite_component>("../res/visual/assets/goal.png", id, false);
        player.add_group(G_CAR);
    }

};

#endif //DEUBER_GOAL_ENTITY_H
