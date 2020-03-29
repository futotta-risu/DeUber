//
// Created by whiwho on 14/03/2020.
//

#ifndef TEMPGAMEMOTOR_GAME_H
#define TEMPGAMEMOTOR_GAME_H

#include <iostream>
#include <vector>
#include <visual/GameVisualizator.h>

#include "SDL.h"
#include "SDL_Image.h"
#include "ECS/ECS.h"
#include "ECS/entity_manager.h"
#include "ECS/asset_manager.h"

class CollisionComponent;

class Game{
private:

    GameVisualizator *gV;
    bool is_running;
    int count;

    int frame_count, timer_fps,last_frame;
public:
    Game();
    ~Game();

    void load_defs(SDL_Renderer** ren_t, const char* map_file_name);

    void main_loop();

    void input();
    void update();
    void render();

    void set_game_visualizator(GameVisualizator* gV_t){
        gV = gV_t;
        ren = gV_t->get_renderer();
    }

    SDL_Renderer **ren;

    static SDL_Event event;
    std::vector<CollisionComponent*> colliders;

    AssetManager ast_man;
    EntityManager e_man;

};

#endif //TEMPGAMEMOTOR_GAME_H
