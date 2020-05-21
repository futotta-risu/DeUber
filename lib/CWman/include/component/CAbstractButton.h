#ifndef WINDOW_MANAGER_CABSTRACTBUTTON_H
#define WINDOW_MANAGER_CABSTRACTBUTTON_H

#include "CComponent.h"
#include "SDL.h"

#include <functional>
#include <algorithm>
#include <utils/colors.h>
#include <utils/collision.h>
#include <CMouse.h>


class CWindow;
class CAbstractButton : public CComponent{
private:

    std::function<void(CWindow*)> action_listener = nullptr;
    CWindow *win = nullptr;
    bool inside = false;
public:
    bool pressed = false;

    CAbstractButton() : CComponent() {};

    ~CAbstractButton() = default;

    void input() override{
        SDL_PumpEvents();

        if(is_inside_rect(get_dst(), CMouse::mouse_x, CMouse::mouse_y)){
            set_pressed(CMouse::isClickLeft());
            set_inside(!CMouse::isClickLeft());
        }else{
            if(pressed && !CMouse::isClickLeft()) set_pressed(false);
            set_inside(false);
        }
    };

    void update() override{};

    void draw(SDL_Renderer *ren) override{draw_CUI(ren);};

    void update_layout() override{};

    void set_action_listener(const std::function<void(CWindow*)>& function_t ){
        action_listener = function_t;
    };

    void set_window(CWindow *win_t){win = win_t;};

    void set_pressed(bool pressed_t){
        if(pressed_t==pressed) return;
        if(!pressed_t) react_button();

        set_background(SDL_Color_dsp(get_background_color(),
                                     (pressed_t) ? -30 : 30));
        pressed = !pressed;
    }

    void set_inside(bool inside_t){
        if(inside_t==inside) return;

        set_background(SDL_Color_dsp(get_background_color(),
                                     (inside_t) ? -10 : 10));
        inside = !inside;
    }

    void react_button(){
        if(action_listener== nullptr || win == nullptr)
            return;
        action_listener(win);
    }
};
#endif //WINDOW_MANAGER_CABSTRACTBUTTON_H
