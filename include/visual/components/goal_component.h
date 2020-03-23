//
// Created by erikberter on 19/03/2020.
//

#ifndef DEUBER_GOAL_COMPONENT_H
#define DEUBER_GOAL_COMPONENT_H

#include "maps/goal.h"
#include "ECS/ECS.h"
#include "ECS/components/transform_component.h"

class Goal_component : public Component {

private:

    Goal* act_goal;
public:
    Goal_component(Goal* act_goal_t){

        act_goal = act_goal_t;

    }

    void init() override{
    }

    void update() override{

       if(!act_goal->active){
           entity->destroy();
       }

    }


};


#endif //DEUBER_GOAL_COMPONENT_H
