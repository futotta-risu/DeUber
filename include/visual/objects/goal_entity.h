//
// Created by erikberter on 19/03/2020.
//

#ifndef DEUBER_GOAL_ENTITY_H
#define DEUBER_GOAL_ENTITY_H

#include "visual/visual_run_handler.h"

#include "maps/goal.h"
#include "visual/components/goal_component.h"

#include "ECS/Components/sprite_component.h"
#include "ECS/Components/transform_component.h"

class goal_entity{
public:

    static void add_goal(Goal* goal_t, Game* gApp, int y, int x) {
        //std::cout << "HGOAL"<< std::endl;
        auto& player = gApp->e_man.man.add_entity();
        player.add_component<TransformComponent>(x*50,y*50);
        player.add_component<Goal_component>(goal_t);
        player.add_component<SpriteComponent>("../res/assets/goal.png",  gApp);
        player.add_group(25);
    }

};

#endif //DEUBER_GOAL_ENTITY_H
