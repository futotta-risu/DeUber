#ifndef WINDOW_MANAGER_CSCROLLPANEL_H
#define WINDOW_MANAGER_CSCROLLPANEL_H

#include <CComponent.h>
#include <CMouse.h>
#include "CPanel.h"
#include "CBar.h"

class CScrollPanel : public CComponent{
private:
    bool updated = false;
    float act_pos = 0;

    CPanel* panel = nullptr;
    CBar* bar;
public:
    CScrollPanel() : CComponent() {
        bar = new CBar();
        set_container();
    };

    void input() override{
        if(!is_inside_rect(get_dst(), CMouse::mouse_x+get_dst()->x, CMouse::mouse_y))
            CMouse::mouse_x+=10000;
        CMouse::mouse_y += static_cast<int>(act_pos);
        bar->input();
        if(panel != nullptr) panel->input();
        CMouse::mouse_y -= static_cast<int>(act_pos);
        if(!is_inside_rect(get_dst(), CMouse::mouse_x+get_dst()->x, CMouse::mouse_y))
            CMouse::mouse_x-=10000;
    };
    void update() override{
        bar->update();
        if(panel != nullptr) panel->update();
    };
    void draw(SDL_Renderer *ren) override{
        if(panel != nullptr) {
            SDL_Texture *view = SDL_CreateTexture(ren,
                    SDL_PIXELFORMAT_RGBA8888,
                    SDL_TEXTUREACCESS_TARGET,
                    panel->get_dst()->w, panel->get_dst()->h);

            SDL_SetRenderTarget(ren, view);
            panel->draw(ren);
            SDL_SetRenderTarget(ren, nullptr);
            act_pos = bar->get_percentage()*(static_cast<float>(panel->get_dst()->h-get_dst()->h));
            SDL_Rect view_src = {0, static_cast<int>(act_pos), get_dst()->w-bar->get_size().w, get_dst()->h};
            SDL_Rect view_dst = {0, 0, get_dst()->w-bar->get_size().w, get_dst()->h};
            SDL_RenderCopy(ren, view, &view_src, &view_dst);
        }
        bar->draw(ren);
    };

    void update_layout() override{
        panel->update_layout();
        set_size({panel->get_size().w+bar->get_size().w,get_dst()->h});
        bar->set_pos({panel->get_size().w,0});
        bar->set_drawn(false);
        bar->set_size({bar->get_size().w,get_dst()->h});
    };

    void set_panel(CPanel* pan){
        panel = pan;
    }
};
#endif //WINDOW_MANAGER_CSCROLLPANEL_H
