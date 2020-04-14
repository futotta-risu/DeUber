//
// Created by erikberter on 20/03/2020.
//

#include "SDL_ttf.h"
#include "CWindow.h"
#include "layout/absolute_layout.h"

#include <iostream>

int CWindow::window_id = 1;

CWindow::CWindow(){
    set_defaults();
    init_SDL(0);
}
CWindow::CWindow(std::string w_title_t){
    set_defaults();
    w_title = w_title_t;
    init_SDL(0);
}

void CWindow::set_defaults(){
    w_height = 600;
    w_width = 800;
    w_id = window_id++;
    w_title = "Default Window";
    window_panel = new CPanel();
    window_panel->set_size(w_height,w_width);
    window_panel->set_resizable(false);
}

void CWindow::init_window(){
    w_active = true;
    run_window();
}


void CWindow::init_SDL(int SDL_flags){
    if(!SDL_WasInit(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_flags)){
        SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
        SDL_StartTextInput();
        if(TTF_Init() < 0)
            std::cout << "Error:" << TTF_GetError() << std::endl;
    }

    win = SDL_CreateWindow(w_title.c_str(),100,100,w_width,w_height,SDL_flags);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}
CWindow::~CWindow(){
    window_panel->~CPanel();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_QuitSubSystem(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
    SDL_Quit();
}

void CWindow::run_window(){
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

void CWindow::window_input(){
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

void CWindow::window_update(){
    window_panel->update();
}

void CWindow::window_render(){
    SDL_RenderClear(ren);
    window_panel->draw(ren);
    SDL_RenderPresent(ren);
}

void CWindow::add(CComponent* component){
    window_panel->add(component);
}

void CWindow::set_layout(WindowLayout* layout){
    window_panel->set_layout(layout);
}

