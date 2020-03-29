//
// Created by whiwho on 14/03/2020.
//

#include <texture_manager.h>
#include "game.h"
#include "game_map.h"
#include "ECS/ECS.h"
#include <string.h>

SDL_Event Game::event;

GameMap map;
Manager map_manager;


Game::Game(){
}

void Game::load_defs(SDL_Renderer** ren_t, const char* map_file_name){
    ren = ren_t;
    ast_man.load_default(ren);
    std::string file_path = "../data/maps/";
    file_path.append(map_file_name);
    map = GameMap(file_path.c_str(), this);
    count = 0;
}

Game::~Game(){
    is_running = false;
    gV->~GameVisualizator();
}

void Game::main_loop() {
    static int last_time=0;
    is_running = true;
    while(is_running){

        last_frame = SDL_GetTicks();

        input();
        update();
        render();

        frame_count++;
        int timer_fps = SDL_GetTicks()-last_frame;
        // TODO make FPS be a changeable option
        // 17 = ceil( 1 s / 60 fps )
        if(timer_fps < 17)
            SDL_Delay(17-timer_fps);
    }
}


void Game::render() {
    SDL_RenderClear(*ren);
    map_manager.draw();
    e_man.draw();
    SDL_RenderPresent(*ren);

}

void Game::update(){
    e_man.update();

}

void Game::input(){
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }
}