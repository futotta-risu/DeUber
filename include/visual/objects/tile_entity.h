//
// Created by erikberter on 18/03/2020.
//

#ifndef DEUBER_TILE_ENTITY_H
#define DEUBER_TILE_ENTITY_H

#include "visual/visual_run_handler.h"

#include "ECS/Components/sprite_component.h"
#include "ECS/Components/transform_component.h"

const std::string tile_names[2] = {
        "../res/assets/tiles/tile-building.png",
        "../res/assets/tiles/tile-floor.png"
};

class tile_entity{
public:
    static void add_tile(std::string id, Game* gApp, int tile_type, int y, int x) {
        auto& player = gApp->e_man.man.add_entity();
        player.add_component<TransformComponent>(x*50,y*50);
        player.add_component<SpriteComponent>(tile_names[tile_type].c_str(),  gApp);
        player.add_group(G_TILES);
    }

};


#endif //DEUBER_TILE_ENTITY_H
