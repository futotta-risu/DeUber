//
// Created by whiwho on 14/03/2020.
//

#ifndef TEMPGAMEMOTOR_GAME_H
#define TEMPGAMEMOTOR_GAME_H

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "stage.h"
#include "ECS/ECS.h"
#include "ECS/entity_manager.h"
#include "ECS/asset_manager.h"
#include "ECS/entity_gen.h"

#include <functional>


using json = nlohmann::json;

class Game{
private:
    // Game Metadata
    bool running;

    int count;

    // Game Value
    unsigned int frame_count, timer_fps,last_frame;

    SDL_Event event{};

    void load_stages(const std::string& path);
    void load_g_entities(const std::string& path);
public:
    // TODO Move to private
    std::map<std::string, G_Entity> g_entities;
    std::map<std::string, json> stages;
    explicit Game(const std::string& config_file_path);
    ~Game();

    // TODO Maybe improve with templates
    void load_defs(std::vector<std::string> *files);

    void main_loop();

    void input();
    void update();
    void render();

    void read_config(const std::string& config_file_path);

    void set_stage(const std::string& stage_t);

    EntityManager e_man;

};

#endif //TEMPGAMEMOTOR_GAME_H
