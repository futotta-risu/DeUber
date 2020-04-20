//
// Created by whiwho on 15/04/2020.
//

#ifndef WINDOW_MANAGER_CSCROLLPANEL_H
#define WINDOW_MANAGER_CSCROLLPANEL_H

#include <CComponent.h>
#include "CPanel.h"
#include "CBar.h"

class CScrollPanel : public CComponent{
private:
    bool updated = false;

    CPanel* panel = nullptr;
    CBar* bar;
public:
    CScrollPanel() : CComponent() {
        bar = new CBar();
        set_container();
    };

    virtual void input(){
        bar->input();
        if(panel != nullptr) panel->input();
    };
    virtual void update(){
        bar->update();
        if(panel != nullptr) panel->update();
    };
    virtual void draw(SDL_Renderer *ren){
        if(panel != nullptr) {
            SDL_Texture *view = SDL_CreateTexture(ren,
                    SDL_PIXELFORMAT_RGBA8888,
                    SDL_TEXTUREACCESS_TARGET,
                    panel->get_dst()->w, panel->get_dst()->h);

            SDL_SetRenderTarget(ren, view);
            panel->draw(ren);
            SDL_SetRenderTarget(ren, NULL);
            float act_pos = bar->get_percentaje()*(static_cast<float>(panel->get_dst()->h-get_dst()->h));
            SDL_Rect view_src = {0, static_cast<int>(act_pos), get_dst()->w-bar->get_size().w, get_dst()->h};
            SDL_Rect view_dst = {0, 0, get_dst()->w-bar->get_size().w, get_dst()->h};
            SDL_RenderCopy(ren, view, &view_src, &view_dst);
        }
        bar->draw(ren);
    };

    virtual void update_layout(){
        panel->update_layout();
        set_size({panel->get_size().w+bar->get_size().w,get_dst()->h});
        bar->set_pos({panel->get_size().w,0});
        bar->set_size({bar->get_size().w,get_dst()->h});
    };

    void set_panel(CPanel* pan){
        panel = pan;
    }
};
#endif //WINDOW_MANAGER_CSCROLLPANEL_H
