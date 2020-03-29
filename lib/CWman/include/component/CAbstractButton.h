//
// Created by whiwho on 24/03/2020.
//

#ifndef WINDOW_MANAGER_CABSTRACTBUTTON_H
#define WINDOW_MANAGER_CABSTRACTBUTTON_H

#include "CComponent.h"
#include "SDL.h"

#include "utils/collision.h"

#include <functional>
#include <algorithm>
#include <utils/colors.h>

class CAbstractButton : public CComponent{
private:

    // Component Metadata
    int button_temp = 0;

    // Component vals
    std::function<void(void)> action_listener = [](){};

    // Component Render

public:
    bool pressed = false;

    CAbstractButton() : CComponent() {};

    CAbstractButton(int pos_x, int pos_y) : CComponent(), pressed{false}{};

    ~CAbstractButton() = default;

    void input() override{
        SDL_PumpEvents();
        int x,y;
        if(SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (is_inside_rect(get_dst(), x, y)) set_pressed(true);
        }else if(pressed){
                set_pressed(false);
                action_listener();
            }
    };

    void update() override{};

    void draw(SDL_Renderer *ren) override{draw_CUI(ren);};

    void update_layout() override{};

    void set_action_listener(std::function<void(void)> function_t ){
        action_listener = function_t;
    };
    
    void set_pressed(bool pressed_t){
        if(pressed_t==pressed) return;

        set_background(SDL_Color_dsp(get_background_color(),
                                     (pressed_t) ? -30 : 30));
        pressed = !pressed;
    }
};
#endif //WINDOW_MANAGER_CABSTRACTBUTTON_H
