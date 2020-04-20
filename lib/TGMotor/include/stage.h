//
// Created by whiwho on 17/04/2020.
//

#ifndef GAME_MOTOR_SCENERY_H
#define GAME_MOTOR_SCENERY_H

#include <fstream>
#include <nlohmann/json.hpp>

class Stage{
private:
    nlohmann::json stage_vals = nullptr;

    std::string stage_id, stage_path;

public:
    Stage() : stage_vals{nullptr}, stage_id{""}, stage_path{""}{};
    Stage(std::string stage_id_t, std::string stage_path_t) : stage_vals{nullptr},
            stage_id{std::move(stage_id_t)}, stage_path{std::move(stage_path_t)}{};

    void load_stage(){
        if(stage_vals != nullptr && !stage_path.empty()){
            std::ifstream i_file(stage_path);
            i_file >> stage_vals;
        }
    }

    nlohmann::json get_json(){
        return stage_vals;
    }


} __attribute__((deprecated));


#endif //GAME_MOTOR_SCENERY_H
