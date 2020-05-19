//
// Created by erikberter on 21/03/2020.
//

#include <iostream>
#include "layout/VerticalFlowLayout.h"
#include <algorithm>

VerticalFlowLayout::VerticalFlowLayout(){
    v_gap = 10;
    h_margin = 10;
    change_layout(WindowLayout::LayoutType::VERTICAL_FLOW);
}

void VerticalFlowLayout::set_size(std::vector<CComponent*> component_list, CComponent* parent_panel){
    Position act_pos = parent_panel->get_pos();
    act_pos.x += h_margin;

    int act_width = 0;
    int act_height = 0;

    for(auto& c : component_list){
        act_pos.y +=v_gap;

        c->set_pos(act_pos);

        if(c->is_container())
            c->update_layout();

        act_width = std::max(2*h_margin + c->get_dst()->w,act_width);
        act_pos.y += c->get_dst()->h;

    }
    act_height = act_pos.y+v_gap - parent_panel->get_pos().y;
    Dimension parent_size = parent_panel->get_size();
    if(parent_panel->is_resizable())
        parent_panel->set_size(
            {std::max(act_width,parent_size.w),
             std::max(act_height,parent_size.h)});

    for(auto& c : component_list){
        Dimension c_size = c->get_size();
        c->set_size({act_width-2*h_margin,c_size.h});
    }

}