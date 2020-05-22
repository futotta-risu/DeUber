#ifndef WINDOW_MANAGER_CTOGGLEBUTTON_H
#define WINDOW_MANAGER_CTOGGLEBUTTON_H
#include <CComponent.h>
#include <utils/collision.h>
#include <misc/CFont.h>
#include <SDL_ttf.h>
#include "CAbstractButton.h"

class CToggleButton : public CAbstractButton{
private:
    std::string button_text;
    CFont font;

    int button_ticks = 0;

    SDL_Texture *tex = nullptr;
public:
    CToggleButton() : button_text{""}{set_default();};
    CToggleButton(std::string button_text_t) : button_text{button_text_t}{set_default();};
    ~CToggleButton() = default;

    void set_default(){
        set_background(244,244,244,255);
        set_size({100,40});
    }
    // Runtime Handlers
    void input() override{
        SDL_PumpEvents();
        if(button_ticks > 0 ) button_ticks--;
        else if(CMouse::isClickLeft()){
            if (is_inside_rect(get_dst(), CMouse::mouse_x, CMouse::mouse_y)){
                set_pressed(!pressed);
                button_ticks = 6;
            }
        }

    };
    void draw(SDL_Renderer* ren) override {
        if(!is_drawn()){
            TTF_Font* font_r = TTF_OpenFont(font.get_font().c_str(), 128);

            SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font_r, button_text.c_str(), font.get_color());
            set_tex_CUI(SDL_CreateTextureFromSurface(ren, surfaceMessage));
            SDL_FreeSurface(surfaceMessage);
            TTF_CloseFont(font_r);

            set_drawn(true);
        }
        draw_CUI(ren);
    };

    bool get_state(){return pressed;};

    void update_layout() override{};
};
#endif //WINDOW_MANAGER_CTOGGLEBUTTON_H
