//
// Created by whiwho on 21/03/2020.
//

#include "component/window_component.h"

int WindowComponent::id = 0;


WindowComponent::WindowComponent() {
    pos_x = 0;
    pos_y = 0;
    visible = true;
    set_dst();
    component_id = "Component_"+std::to_string(id++);
}