//
// Created by erikberter on 21/03/2020.
//

#include <iostream>
#include "layout/vertical_flow_layout.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

VerticalFlowLayout::VerticalFlowLayout(){
    v_gap = 10;
    h_margin = 10;
}

void VerticalFlowLayout::set_size(std::vector<WindowComponent*> component_list, SDL_Rect* coords){
    int act_pos_x = coords->x+h_margin;
    int act_pos_y = coords->y;
    int act_width = 0;
    int act_height = 0;
    for(auto& c : component_list){
        //std::cout << c->get_id() << std::endl;
        act_pos_y+=v_gap;

        c->get_dst()->x = act_pos_x;
        c->get_dst()->y = act_pos_y;

        if(c->is_container())
            c->update_layout();

        /*if(act_pos_y+c->get_dst()->h >= coords->y+coords->h ||
           coords->x+c->get_dst()->w >= coords->x + coords->w){
            //std::cout << " GOALAL " << c->get_id() << ": " << std::endl;
            //std::cout << "ACT =" << act_pos_x << ":" << act_pos_y << std::endl;
            //std::cout << "coords=" << coords->x << ":" << coords->y << ":" << coords->h << ":" << coords->w << std::endl;
            //std::cout << "comps=" << c->get_dst()->x << ":" << c->get_dst()->y << ":" << c->get_dst()->h << ":" << c->get_dst()->w << std::endl;
            c->visible = false;
            break;
        }*/

        act_width = MAX(2*h_margin + c->get_dst()->w,act_width);
        act_pos_y += c->get_dst()->h;

    }
    act_height = act_pos_y+v_gap - coords->y;
    coords->h = MAX(act_height,coords->h);
    coords->w = MAX(act_width,coords->w);

}