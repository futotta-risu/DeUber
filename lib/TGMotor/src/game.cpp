//
// Created by whiwho on 14/03/2020.
//
#include "game.h"

#include "g_constants.h"
#include <ECS/Components/component_helper_t.h>
#include <renderer.h>

#include "utils/files.h"
#include <plog/Log.h>



Game::Game(const std::string& config_file_path){
    plog::init(plog::debug, "logs/running.log");
    read_config(config_file_path);
    running = false;
    count  = 0;
    frame_count = timer_fps= last_frame = 0u;
}



void Game::load_defs(std::vector<std::string> *files){
    load_default_components();
    PLOG_DEBUG << "Loading Assets";
    GameRender::ast_man.load_resources(GameRender::ren, "../res/assets/");
    PLOG_DEBUG << "Loading Entities";
    load_g_entities("../res/entities/");
    PLOG_DEBUG << "Loading Stages";
    load_stages("../res/stage/");

    // TODO Implement Extra resources loading
}

void Game::set_stage(const std::string& stage_t){
    e_man.man.clear();
    if(!stages.count(stage_t))
        return; // TODO Add error in case no stage found

    json *stage_data = &stages[stage_t];
    if(stage_data->contains("entities")){
        for(auto& c : (*stage_data)["entities"].items()){
            auto& temp_ent = e_man.man.add_entity();
            temp_ent.add_group(G_PLAYER);
            if(!c.value().contains("components"))
                continue;
            for(auto& c_comp : c.value()["components"].items())
                temp_ent.add_component(ComponentMapSCT[c_comp.key()], &c_comp.value());
        }
    }
}
Game::~Game(){
    running = false;
}

void Game::main_loop() {
    running = true;
    while(running){

        last_frame = SDL_GetTicks();

        input();
        update();
        render();

        frame_count++;
        timer_fps = SDL_GetTicks()-last_frame;
        // TODO make FPS be a changeable option
        // 17 = ceil( 1 s / 60 fps )
        if(timer_fps < 17)
            SDL_Delay(17-timer_fps);
    }
}


void Game::render() {
    SDL_RenderClear(GameRender::ren);
    e_man.draw();
    SDL_RenderPresent(GameRender::ren);

}

void Game::update(){
    e_man.update();

}

void Game::input(){
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            running = false;
            break;
        default:
            break;
    }
}

void Game::load_g_entities(const std::string& path){
    const char* stg_regex = constants::ASSET_REGEX_PER;
    std::map<std::string, G_Entity> *g_ent_vec_p = &g_entities;

    sp_str::function_v_ss add_stage= [g_ent_vec_p](const std::string& a, const std::string& b){
        g_ent_vec_p->emplace(a, G_Entity(b));
    };

    sp_str::functional_vector vec_t = {std::make_pair(stg_regex, add_stage)};
    file_rec(path, vec_t);
}

void Game::load_stages(const std::string& path){
    std::map<std::string, json> *stage_vec_p = &stages;

    sp_str::function_v_ss add_stage = [stage_vec_p](const std::string& a,const std::string& b){
        stage_vec_p->emplace(a, get_json(b));
    };

    sp_str::functional_vector vec_t = {std::make_pair(constants::ASSET_REGEX_STG, add_stage)};
    file_rec(path, vec_t);
}



void Game::read_config(const std::string& config_file_path){
}