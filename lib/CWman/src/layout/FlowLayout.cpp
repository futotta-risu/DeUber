#include <iostream>
#include "layout/FlowLayout.h"
#include <algorithm>

FlowLayout::FlowLayout(){
    h_gap = 10;
    v_margin = 10;
    change_layout(WindowLayout::LayoutType::FLOW);
}

void FlowLayout::set_size(std::vector<CComponent*> component_list, CComponent* parent_panel){
    Position act_pos = parent_panel->get_pos();
    act_pos.y += v_margin;

    int act_width = 0;
    int act_height = 0;

    for(auto& c : component_list){
        act_pos.x +=h_gap;

        c->set_pos(act_pos);

        if(c->is_container())
            c->update_layout();

        act_height = std::max(2*v_margin + c->get_dst()->h,act_height);
        act_pos.x += c->get_dst()->w;

    }
    act_width = act_pos.x+h_gap - parent_panel->get_pos().x;
    Dimension parent_size = parent_panel->get_size();
    if(parent_panel->is_resizable())
        parent_panel->set_size(
                {std::max(act_width,parent_size.w),
                 std::max(act_height,parent_size.h)});

    for(auto& c : component_list){
        Dimension c_size = c->get_size();
        c->set_size({c_size.w,act_height-2*v_margin});
    }

}