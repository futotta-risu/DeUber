//
// Created by erikberter on 19/03/2020.
//

#ifndef DEUBER_GOAL_ENTITY_H
#define DEUBER_GOAL_ENTITY_H

#include "visual/visual_run_handler.h"
#include "ECS/components/components.h"
#include "ECS/components/random_movement_component.h"

#include "maps/goal.h"
#include "visual/components/goal_component.h"

class goal_entity{
public:

    static void add_goal(Goal* goal_t, GameApp* gApp, int y, int x) {
        auto& player = gApp->add_entity();
        player.add_component<Transform_component>(x*64,y*64);
        player.add_component<Goal_component>(goal_t);
        player.add_component<Sprite_component>("../res/visual/assets/goal.png",  false);
        player.add_group(2);
    }

};

#endif //DEUBER_GOAL_ENTITY_H
