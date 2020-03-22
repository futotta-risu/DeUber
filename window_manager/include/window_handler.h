//
// Created by whiwho on 20/03/2020.
//

#ifndef WINDOWMANAGER_WINDOW_HANDLER_H
#define WINDOWMANAGER_WINDOW_HANDLER_H


#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "layout/window_layout.h"
#include "component/panel_component.h"
#include <string>

const unsigned short WINDOW_FPS = 20;
constexpr unsigned short WINDOW_FPS_DELAY = 1000/WINDOW_FPS;
class WindowHandler{
private:

    SDL_Window* win;

    SDL_Event w_event;

    bool w_active;

    int w_id;
    int w_height, w_width;
    std::string w_title;

    SDL_Rect window_size;

    CPanel *window_panel;

    void init_SDL(int SDL_flags);

    void run_window();
    void window_input();
    void window_update();
    void window_render();
public:
    static int window_id;

    WindowHandler();
    WindowHandler(std::string w_title_t, int w_height_t, int w_width_t);

    void set_defaults();

    SDL_Renderer* ren;
    void init_window();
    void init_window(int SDL_flags);

    void set_layout(WindowLayout* layout);
    void add(WindowComponent* component);

};

#endif //WINDOWMANAGER_WINDOW_HANDLER_H
