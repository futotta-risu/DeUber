//
// Created by erikberter on 20/03/2020.
//

#ifndef WINDOWMANAGER_WINDOW_HANDLER_H
#define WINDOWMANAGER_WINDOW_HANDLER_H



#include "SDL.h"

#include "layout/WindowLayout.h"
#include "component/CPanel.h"
#include <string>
#include <utils/SDL2_conv.h>

#include "layout/BorderLayout.h"

const unsigned short WINDOW_FPS = 60;
constexpr unsigned short WINDOW_FPS_DELAY = 1000/WINDOW_FPS;

namespace CWindowData{
    extern unsigned int n_window;
}

class CWindow{
private:
    // Window Metadata
    int w_id;

    // Window Values
    bool w_active;
    int w_height, w_width;
    std::string w_title;

    // Window Render
    SDL_Window* win;
    SDL_Event w_event;
    CPanel *window_panel;

    SDL_Renderer* ren;

    // Window Functions
    void run_window();

    void window_input();
    void window_update();
    void window_render();

    void set_defaults();
    void init_SDL(int SDL_flags);

public:
    static int window_id;

    CWindow();
    explicit CWindow(std::string w_title_t);
    ~CWindow();
    void dispose();

    void set_size(int w,int h){
        w_width = w;
        w_height = h;
        SDL_SetWindowSize(win,w,h);
    }

    void set_title(const std::string& title_t){
        SDL_SetWindowTitle(win, title_t.c_str());
    }
    std::string get_title(){
        return SDL_GetWindowTitle(win);
    }

    void set_resizable(bool resizable){
        SDL_SetWindowResizable(win,to_SDL_bool(resizable));
    }

    void init_window();

    void set_layout(WindowLayout* layout);
    void add(CComponent* component);
    void add(CComponent* component, BorderLayout::BLPosition p);

    CComponent* get_component_by_id(const std::string& id){
        return window_panel->get_component_by_id(id);
    };

    SDL_Renderer** get_render(){
        return &ren;
    }

    CPanel* get_panel(){
        return window_panel;
    }
};

#endif //WINDOWMANAGER_WINDOW_HANDLER_H
