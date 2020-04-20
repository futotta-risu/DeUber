//
// Created by whiwho on 17/04/2020.
//

#ifndef GAME_MOTOR_ENTITY_GEN_H
#define GAME_MOTOR_ENTITY_GEN_H

#include <vector>
#include <nlohmann/json.hpp>
#include "ECS.h"

#include <string>
#include <fstream>


/**
 * Generic Entity is the class that saves the data
 * of the entity it represents. It does it without
 * having to invoke the actual classes, but rather
 * saving them in a map<string, json>
 */
class G_Entity{
private:
    /**
     * Vector of all the Components a ceratin Entity will have.
     * The vector is of type
     *      std::string     Name of the Component
     *      json            Data passed to the Component contructor
     */
    std::vector<std::pair<std::string, json>> ent_components;
    std::string id;
public:

    G_Entity() = default;

    G_Entity(const std::string& path){
        nlohmann::json entity_vals;

        std::ifstream i_file(path);
        i_file >> entity_vals;
        id = entity_vals["metadata"]["id"];
        nlohmann::json data_comps = entity_vals["components"];

        for (auto& c : data_comps.items())
            ent_components.emplace_back(std::make_pair(c.key(), c.value()));
        i_file.close();
    }

    std::vector<std::pair<std::string, nlohmann::json> > get_ent_components(){
        return ent_components;
    }
};

#endif //GAME_MOTOR_ENTITY_GEN_H
