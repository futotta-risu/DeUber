//
// Created by erikberter on 15/03/2020.
//

#include "game_map.h"
#include "texture_manager.h"
#include <fstream>

#include "ECS/Components/transform_component.h"
#include "ECS/Components/sprite_component.h"

GameMap::GameMap(const char* map_sheet, Game *gApp){
    load_map(map_sheet,gApp);
}

GameMap::~GameMap(){
    //SDL_DestroyTexture(grass);
    //SDL_DestroyTexture(water);
}



void GameMap::load_map(const char* map_sheet, Game *gApp){
    file_name = map_sheet;
    std::string res_path = "../res/assets/tiles/tile_b";

    // LOADING MAP RESOURCES
    std::ifstream res_infile(res_path);
    std::map<int, std::string> tex_map;

    std::string tile_name;
    int n_lines, id;

    res_infile >> n_lines;

    for(size_t i = 0; i< n_lines; i++){
        res_infile >> id >> tile_name;
        tex_map[id] =  ("../res/assets/tiles/" +tile_name);
    }
    res_infile.close();

    // LOAD MAP FILE
    std::cout << "---------" << std::endl;
    std::ifstream map_infile(file_name);
    map_infile >> map_height >> map_width;
    reshape_map();

    std::string line;
    for(int i = 0; i < map_height; i++){
        map_infile >> line;
        for(int j = 0; j < map_width; j++){
            map[i][j] = line[j]-'0';
            if(map[i][j]==3) map[i][j] = 0;

            auto& tile = gApp->e_man.man.add_entity();
            tile.add_component<TransformComponent>(j*50,i*50,50,50,1);
            tile.add_component<SpriteComponent>(tex_map[map[i][j]].c_str(),gApp);
            tile.add_group(G_TILES);

        }
    }
    map_infile.close();
}

#include <iostream>

void GameMap::print_map(){
    for(int i = 0; i < map_height; i++){
        for(int j = 0; j < map_width; j++)
            std::cout << map[i][j] << " ";
        std::cout << std::endl;
    }
}


void GameMap::reshape_map(){
    map = new int*[map_height];
    for(int i = 0; i < map_height; i++)
        map[i] = new int[map_width];
}

