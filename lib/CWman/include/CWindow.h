//
// Created by erikberter on 20/03/2020.
//

#ifndef WINDOWMANAGER_WINDOW_HANDLER_H
#define WINDOWMANAGER_WINDOW_HANDLER_H



#include "SDL.h"

#include "layout/WindowLayout.h"
#include "component/CPanel.h"
#include <string>

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
    CWindow(std::string w_title_t);
    ~CWindow();
    void dispose();

    void set_size(int w,int h){
        w_width = w;
        w_height = h;
    }

    void init_window();

    void set_layout(WindowLayout* layout);
    void add(CComponent* component);
    void add(CComponent* component, BorderLayout::BLPosition p);

    CComponent* get_component_by_id(std::string id){
        return window_panel->get_component_by_id(id);
    };

    SDL_Renderer** get_render(){
        return &ren;
    }
};

#endif //WINDOWMANAGER_WINDOW_HANDLER_H
