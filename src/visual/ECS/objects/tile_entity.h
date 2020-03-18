//
// Created by whiwho on 18/03/2020.
//

#ifndef DEUBER_TILE_ENTITY_H
#define DEUBER_TILE_ENTITY_H

#include "../../visual_run_handler.h"
#include "../Components/components.h"
#include "../Components/random_movement_component.h"

static std::string tile_names[2] = {
        "../res/visual/assets/tile-building.png",
        "../res/visual/assets/tile-floor.png"
};

class tile_entity{
public:

    static void add_tile(std::string id, int tile_type, int y, int x) {
        auto& player(visual_run_handler::ent_man.man.add_entity());
        player.add_component<Transform_component>(x*64,y*64);
        player.add_component<Sprite_component>(tile_names[tile_type].c_str(), id, false);
        player.add_group(G_TILES);
    }

};


#endif //DEUBER_TILE_ENTITY_H
