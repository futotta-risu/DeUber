//
// Created by whiwho on 18/03/2020.
//

#ifndef DEUBER_VISUAL_RUN_HANDLER_H
#define DEUBER_VISUAL_RUN_HANDLER_H

#include "visual/ECS/EntityManager.h"
#include "visual/ECS/asset_manager.h"
#include "algorithms/algorithm_type.h"
#include "algorithms/generic_algorithm.h"

#include "../maps/map.h"

#include "SDL.h"
#include "SDL_image.h"

#include "../running_info.h"

class Collision_component;

const int WIDTH = 800, HEIGH = 600;



class visual_run_handler {
private:
    SDL_Window* win;

public:

    int counter;

    std::vector<car> car_list;
    Map mapa;
    algorithm_type alg_type;
    generic_algorithm *algorithm;

    running_menu_data run_dat;

    visual_run_handler(std::string map_file_name, algorithm_type alg_t);
    ~visual_run_handler();

    void main_loop();
    void input();
    void update();
    void render();

    void set_fps(int fps){
        if(fps>0 && fps <120)
            run_dat.animated_fps = fps;
    }

    bool is_running;
    static SDL_Renderer *ren;
    static SDL_Event event;
    static EntityManager ent_man;
    static Asset_manager ast_man;
    static std::vector<Collision_component*> colliders;
};


#endif //DEUBER_VISUAL_RUN_HANDLER_H
