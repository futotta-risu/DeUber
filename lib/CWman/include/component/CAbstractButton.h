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
    int button_temp = 0;

    std::function<void(CWindow*)> action_listener = nullptr;
    CWindow *win = nullptr;
public:
    bool pressed = false;

    CAbstractButton() : CComponent() {};

    CAbstractButton(int pos_x, int pos_y) : CComponent(), pressed{false}{};

    ~CAbstractButton() = default;

    void input() override{
        SDL_PumpEvents();
        if(CMouse::isClickLeft()) {
            if(is_inside_rect(get_dst(), CMouse::mouse_x, CMouse::mouse_y))
                set_pressed(true);
        }else if(pressed){
                set_pressed(false);
                if(action_listener== nullptr || win == nullptr)
                    return;
                action_listener(win);
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

        set_background(SDL_Color_dsp(get_background_color(),
                                     (pressed_t) ? -30 : 30));
        pressed = !pressed;
    }
};
#endif //WINDOW_MANAGER_CABSTRACTBUTTON_H
