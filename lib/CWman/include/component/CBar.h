#ifndef WINDOW_MANAGER_CBAR_H
#define WINDOW_MANAGER_CBAR_H

#include <CComponent.h>
#include <utils/collision.h>

class CBar : public CComponent{
private:
    int     max_height // Bar Height
        ,   act_height; // Bar position

    bool pressed;

    SDL_Color bar_color, bar_back;

    void _set_pressed(bool pressed_t){
        if(pressed_t == pressed) return;
        pressed = pressed_t;
        set_selected(pressed_t);
    }

public:

    CBar() : CComponent(){set_default();};
    ~CBar() = default;

    void set_default(){
        set_background(0,244,244,255);
        set_border_size(0);

        set_minimum_size({10,40});
        set_size({20,500});

        bar_color = {112,111,111};
        bar_back = {219,219,219};
        max_height = 50;
        act_height = max_height/2;
        set_drawn(false);
    }
    void input() override {
        SDL_PumpEvents();
        if(!is_selectable()) return;
        int x,y;
        if(SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_LEFT)){
            if (is_inside_rect(get_dst(), x, y) || pressed){
                act_height = std::min(std::max(get_dst()->y+max_height/2, y),
                        get_dst()->y+get_dst()->h-max_height/2);
                set_drawn(false);_set_pressed(true);}
        }else _set_pressed(false);

    }
    void update() override {};
    void draw(SDL_Renderer *ren) override{
        draw_CUI(ren);
        if(!is_drawn()){
            SDL_Texture *bar_tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,
                                                       SDL_TEXTUREACCESS_TARGET, get_dst()->w, get_dst()->h);
            SDL_SetRenderTarget(ren, bar_tex);
            SDL_RenderClear(ren);
            SDL_SetRenderDrawColor(ren, bar_back.r,bar_back.g,bar_back.b,bar_back.a);
            SDL_Rect size_back = {0,0,get_dst()->w,get_dst()->h};
            SDL_RenderFillRect(ren, &size_back);
            SDL_SetRenderDrawColor(ren, bar_color.r,bar_color.g,bar_color.b,bar_color.a);
            SDL_Rect size = {0,act_height-max_height/2-get_dst()->y,get_size().w,max_height};

            SDL_RenderFillRect(ren, &size);
            SDL_SetRenderTarget(ren, nullptr);
            set_tex_CUI(bar_tex);
            set_drawn(true);
        }

    }
    void update_layout(){};

    int get_act_height(){return act_height-max_height/2;};
    int get_bar_height(){return max_height;};
    float get_percentage(){
        float act_percentage = static_cast<float>(act_height-max_height/2)/ static_cast<float>(get_dst()->h-max_height);
        return act_percentage;
    }
};

#endif //WINDOW_MANAGER_CBAR_H
