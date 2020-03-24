//
// Created by erikberter on 21/03/2020.
//

#ifndef WINDOWMANAGER_PANEL_COMPONENT_H
#define WINDOWMANAGER_PANEL_COMPONENT_H

#include <vector>
#include <iostream>
#include "window_component.h"
#include "layout/window_layout.h"
#include "layout/absolute_layout.h"
#include "layout/vertical_flow_layout.h"

class CPanel : public WindowComponent{
private:

    bool updated = false;

    std::vector<WindowComponent*> component_list;

    WindowLayout* panel_layout;

    SDL_Color bg_color = {200,200,200,255};


public:

    CPanel() : WindowComponent(){
        panel_layout = new VerticalFlowLayout();
        set_container();
    };

    void set_size(int height, int width){
        SDL_Rect* dims = get_dst();
        dims->h = height;
        dims->w = width;
    }

    void input() override{
        for(auto& c : component_list)
            c->input();
    }
    void update() override{
        for(auto& c : component_list)
            c->update();
    }
    void draw(SDL_Renderer *ren) override{
        SDL_SetRenderDrawColor(ren, bg_color.r,bg_color.g,bg_color.b,bg_color.a);
        SDL_RenderFillRect(ren,get_dst());
        for(auto& c : component_list){
            if(!c->visible)
                continue;
            c->draw(ren);
        }
        if(!updated){
            panel_layout->set_size(component_list, get_dst());
            updated = !updated;
        }
    }

    void add(WindowComponent* component){
        component_list.emplace_back(component);
        update_layout();
    }

    void set_layout(WindowLayout* layout_t){
        panel_layout = layout_t;
        update_layout();
    }

    void update_layout() override{
        updated = false;
        panel_layout->set_size(component_list, get_dst());
    }

    void set_background_color(SDL_Color bg_color_t){
        bg_color = bg_color_t;
    }
};

#endif //WINDOWMANAGER_PANEL_COMPONENT_H
