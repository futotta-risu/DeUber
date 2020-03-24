//
// Created by erikberter on 20/03/2020.
//

#ifndef WINDOWMANAGER_COMPONENT_BUTTON_H
#define WINDOWMANAGER_COMPONENT_BUTTON_H
#include "window_component.h"

#include "SDL_ttf.h"
#include "SDL.h"
#include <functional>
#include <iostream>
#include <algorithm>

class ComponentButton : public WindowComponent{
private:

    // Component Metadata
    std::string button_text;
    int button_temp;

    // Component vals
    std::function<void(void)> action_listener = [](void ){};

    // Component Render
    SDL_Texture* tex;
    SDL_Color bg_color = {233,233,233},
        border_color = {0,0,0},
        text_color = {0,0,0};

public:
    bool is_pressed = false;

    ComponentButton() : WindowComponent(), button_text{""}, is_pressed{false}{};
    ComponentButton(std::string button_text_t) : WindowComponent(),button_text{button_text_t}, is_pressed{false}{};
    ComponentButton(int pos_x, int pos_y) : WindowComponent(pos_x,pos_y),button_text{""}, is_pressed{false}{};
    ComponentButton(std::string button_text_t, int pos_x, int pos_y) : WindowComponent(pos_x,pos_y),
        button_text{button_text_t}, is_pressed{false}{};

    ~ComponentButton(){
        SDL_DestroyTexture(tex);
    }

    void input() override{
        if(is_pressed) return;
        SDL_PumpEvents();
        if(SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
            int x, y;
            SDL_GetMouseState(&x, &y);
            SDL_Rect *coords = get_dst();
            if (coords->x < x && coords->x + coords->w > x && coords->y < y && coords->y + coords->h > y){
                is_pressed = true;
                button_temp = 3;
                std::cout << "Pulsado el boton" << get_id() << std::endl;
                action_listener();
            }

        }
    };
    void update() override{
        if(is_pressed){
            if(button_temp--==0)
                is_pressed = false;
        }
    };

    void draw(SDL_Renderer *ren) override{
        if(!is_pressed) SDL_SetRenderDrawColor(ren, bg_color.r,bg_color.g,bg_color.b,255);
        else SDL_SetRenderDrawColor(ren, std::max(0,bg_color.r-30),
                std::max(0,bg_color.g-30),std::max(0,bg_color.b-30),255);

        SDL_RenderFillRect(ren,get_dst());
        SDL_SetRenderDrawColor(ren, border_color.r,border_color.g,border_color.b,255);
        SDL_RenderDrawRect(ren, get_dst());
        SDL_SetRenderDrawColor(ren, 255,255,255,255);

        if(!is_drawed()){
            TTF_Font* font = TTF_OpenFont("../res/font/Roboto/Roboto-Regular.ttf", 32);

            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, button_text.c_str(), text_color);
            tex = SDL_CreateTextureFromSurface(ren, surfaceMessage);
            SDL_FreeSurface(surfaceMessage);
            TTF_CloseFont(font);
            //SDL_QueryTexture(Message, NULL, NULL, &(get_dst()->w), &(get_dst()->h));
            set_drawed();
        }

        SDL_RenderCopy(ren, tex, NULL, get_dst());
    }

    void update_layout() override{};

    void set_action_listener(std::function<void(void)> function_t ){
        action_listener = function_t;
    };
};

#endif //WINDOWMANAGER_COMPONENT_BUTTON_H
