#include "layout/BorderLayout.h"
#include <algorithm>

BorderLayout::BorderLayout(){
    v_gap       = 10;
    h_margin    = 10;
    change_layout(WindowLayout::LayoutType::BORDER);
    for(auto & comp : comps)
        comp=nullptr;

}

void BorderLayout::set_size(std::vector<CComponent*> component_list, CComponent* parent_panel){
    Position act_pos = parent_panel->get_pos();
    act_pos.x += h_margin;

    int act_width = 0;
    int act_height = 0;

    for(auto & comp : comps)
        if(comp!= nullptr)
            if(comp->is_container()) comp->update_layout();


    int temp_w[5], temp_h[5];
    for(int i = 0; i < 5; i++){
        temp_w[i] = (comps[i]== nullptr) ? 0 : comps[i]->get_dst()->w;
        temp_h[i] = (comps[i]== nullptr) ? 0 : comps[i]->get_dst()->h;
    }

    int height_t = std::max(std::max(temp_h[2],temp_h[3]),temp_h[4]);

    act_width   = std::max(std::max(temp_w[0], temp_w[1]), temp_w[2]+temp_w[3]+temp_w[4]);
    act_height  = temp_h[0] + temp_h[1] + height_t;

    if(comps[0]!= nullptr)
        comps[0]->set_pos({0,0});                                   // NORTH
    if(comps[3]!= nullptr)
        comps[3]->set_pos({0, temp_h[0]});                          // WEST
    if(comps[4]!= nullptr)
        comps[4]->set_pos({temp_w[2], temp_h[0]});                  // CENTER
    if(comps[2]!= nullptr)
        comps[2]->set_pos({temp_w[4]+temp_w[3], temp_h[0]});        // EAST
    if(comps[1]!= nullptr)
        comps[1]->set_pos({0,temp_h[0] + height_t});                 // SOUTH

    Dimension parent_size = parent_panel->get_size();
    if(parent_panel->is_resizable())
        parent_panel->set_size(
                {std::max(act_width,parent_size.w),
                 std::max(act_height,parent_size.h)});

    if(comps[0]!= nullptr)
        comps[0]->set_size({act_width-2*h_margin,temp_h[0]});

    for(int i = 1; i <= 3; i++)
        if(comps[i]!= nullptr)
            comps[i]->set_size({temp_w[i],height_t});

    if(comps[4]!= nullptr)
        comps[4]->set_size({act_width-2*h_margin,temp_h[4]});
}