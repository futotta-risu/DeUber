//
// Created by erikberter on 18/03/2020.
//

#ifndef DEUBER_TILE_ENTITY_H
#define DEUBER_TILE_ENTITY_H

#include "visual/visual_run_handler.h"
#include "ECS/components/components.h"
#include "ECS/components/random_movement_component.h"

const std::string tile_names[2] = {
        "../res/visual/assets/tile-building.png",
        "../res/visual/assets/tile-floor.png"
};

class tile_entity{
public:
    static void add_tile(std::string id, GameApp* gApp, int tile_type, int y, int x) {
        auto& player = gApp->add_entity();
        player.add_component<Transform_component>(x*64,y*64);
        player.add_component<Sprite_component>(tile_names[tile_type].c_str(),  false);
        player.add_group(1);
    }

};


#endif //DEUBER_TILE_ENTITY_H
