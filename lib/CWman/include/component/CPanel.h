//
// Created by erikberter on 21/03/2020.
//

#ifndef WINDOWMANAGER_PANEL_COMPONENT_H
#define WINDOWMANAGER_PANEL_COMPONENT_H

#include <vector>
#include <iostream>
#include "CComponent.h"
#include "layout/window_layout.h"
#include "layout/absolute_layout.h"
#include "layout/vertical_flow_layout.h"

class CPanel : public CComponent{
private:
    bool updated = false;

    std::vector<CComponent*> component_list;
    WindowLayout* panel_layout;
    SDL_Color bg_color = {200,200,200,255};

public:

    CPanel() : CComponent(){
        panel_layout = new VerticalFlowLayout();
        set_container();
        component_list = {};
    };

    void set_size(int height, int width){
        SDL_Rect* dims = get_dst();
        dims->h = height;
        dims->w = width;
    }

    void input() override{ for(auto& c : component_list) c->input(); }
    void update() override{ for(auto& c : component_list) c->update(); }
    void draw(SDL_Renderer *ren) override{
        draw_CUI(ren);
        for(auto& c : component_list){
            if(!c->visible) continue;
            c->draw(ren);
        }
        if(!updated)
            panel_layout->set_size(component_list, this),
            updated = !updated;

    }

    void update_layout() override{
        updated = false;
        panel_layout->set_size(component_list, this);
    }

    void add(CComponent* component){
        component->set_parent(this);
        component_list.emplace_back(component);
        update_layout();
    }

    void set_layout(WindowLayout* layout_t){
        panel_layout = layout_t;
        update_layout();
    }



    CComponent* get_component_by_id(std::string id){

        for(auto c : component_list){
            if(c->get_id()==id) return c;
            if(c->is_container()){
                CComponent *ret = static_cast<CPanel*>(c)->get_component_by_id(id);
                if(ret!= nullptr) return ret;
            }
        }
        return nullptr;
    };
};

#endif //WINDOWMANAGER_PANEL_COMPONENT_H
