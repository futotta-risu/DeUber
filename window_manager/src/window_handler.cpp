//
// Created by whiwho on 20/03/2020.
//

#include <SDL_ttf.h>
#include "window_handler.h"
#include "layout/absolute_layout.h"

#include <iostream>

int WindowHandler::window_id = 1;



WindowHandler::WindowHandler(){
    w_id = window_id++;
    w_height = 600;
    w_width = 800;
    w_title = "Default Window";
    window_size.x = 0;
    window_size.y = 0;
    window_size.w = w_width;
    window_size.h = w_height;
    set_defaults();
}
WindowHandler::WindowHandler(std::string w_title_t, int w_height_t, int w_width_t){
    w_id = window_id++;
    w_height = w_height_t;
    w_width = w_width_t;
    w_title = w_title_t;
    window_size.x = 0;
    window_size.y = 0;
    window_size.w = w_width;
    window_size.h = w_height;
    set_defaults();
}

void WindowHandler::set_defaults(){
    window_panel = new CPanel();
    window_panel->set_size(w_height,w_width);
}

void WindowHandler::init_window(){
    init_SDL(0);
    w_active = true;
    run_window();
}
void WindowHandler::init_window(int SDL_flags){
    init_SDL(SDL_flags);
    w_active = true;
    run_window();
}

void WindowHandler::init_SDL(int SDL_flags){
    SDL_Init(0);
    SDL_CreateWindowAndRenderer(w_width, w_height, SDL_flags, &win, &ren);
    SDL_SetWindowTitle(win, w_title.c_str());
    if(TTF_Init() < 0)
        std::cout << "Error:" << TTF_GetError() << std::endl;
}

void WindowHandler::run_window(){
    int last_frame, act_frame;
    while(w_active){
        last_frame = SDL_GetTicks();
        window_input();
        window_update();
        window_render();

        act_frame = SDL_GetTicks();
        if(act_frame-last_frame<WINDOW_FPS_DELAY)
            SDL_Delay(WINDOW_FPS_DELAY-(act_frame-last_frame));
    }
}

void WindowHandler::window_input(){
    SDL_PollEvent(&w_event);
    switch(w_event.type){
        case SDL_QUIT:
            w_active = false;
            break;
        default:
            break;
    }
    window_panel->input();
}

void WindowHandler::window_update(){
    window_panel->update();
}

void WindowHandler::window_render(){
    SDL_RenderClear(ren);
    window_panel->draw(ren);
    SDL_RenderPresent(ren);
}

void WindowHandler::add(WindowComponent* component){
    window_panel->add(component);
}

void WindowHandler::set_layout(WindowLayout* layout){
    window_panel->set_layout(layout);
}