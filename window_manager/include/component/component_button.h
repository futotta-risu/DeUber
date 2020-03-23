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

class ComponentButton : public WindowComponent{
private:

    std::string button_text;
    int button_temp;

    std::function<void(void)> action_listener = [](void ){};

public:
    ComponentButton() : WindowComponent(), button_text{""}, is_pressed{false}{};
    ComponentButton(std::string button_text_t) : WindowComponent(),button_text{button_text_t}, is_pressed{false}{};
    ComponentButton(int pos_x, int pos_y) : WindowComponent(pos_x,pos_y),button_text{""}, is_pressed{false}{};
    ComponentButton(std::string button_text_t, int pos_x, int pos_y) : WindowComponent(pos_x,pos_y),
        button_text{button_text_t}, is_pressed{false}{};

    bool is_pressed = false;

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
        //std::cout << "jejej :" << get_id() << ":::"<< get_dst()->x << "-"<<get_dst()->y << "-" << get_dst()->w << "-" << get_dst()->h<< std::endl;
        if(!is_pressed) SDL_SetRenderDrawColor(ren, 255,255,255,255);
        else SDL_SetRenderDrawColor(ren, 200,200,200,255);
        SDL_RenderFillRect(ren,get_dst());
        SDL_SetRenderDrawColor(ren, 233,233,233,255);
        SDL_RenderDrawRect(ren, get_dst());
        SDL_SetRenderDrawColor(ren, 255,255,255,255);

        TTF_Font* Sans = TTF_OpenFont("../res/font/OpenSans-Bold.ttf", 32);
        SDL_Color Blue = {0, 0, 255};

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, button_text.c_str(), Blue);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
        SDL_FreeSurface(surfaceMessage);

        //SDL_QueryTexture(Message, NULL, NULL, &(get_dst()->w), &(get_dst()->h));
        SDL_RenderCopy(ren, Message, NULL, get_dst());
        SDL_DestroyTexture(Message);

    }

    void update_layout() override{};

    void set_action_listener(std::function<void(void)> function_t ){
        action_listener = function_t;
    };
};

#endif //WINDOWMANAGER_COMPONENT_BUTTON_H
