//
// Created by erikberter on 19/03/2020.
//

#ifndef DEUBER_GOAL_COMPONENT_H
#define DEUBER_GOAL_COMPONENT_H

#include "maps/goal.h"
#include "ECS/ECS.h"

namespace ComponentHelper{
    extern ComponentHelper::ComponentType GOAL;
}
class goal_component : public Component {
private:
    Goal* act_goal = nullptr;
public:
    goal_component() = default;

    void init() override{}
    void update() override{
       if(!act_goal->active)
           entity->destroy();
    }

    void set_case(Goal* act_goal_t){
        act_goal = act_goal_t;
    }

};


#endif //DEUBER_GOAL_COMPONENT_H
