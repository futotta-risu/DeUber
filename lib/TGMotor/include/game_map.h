//
// Created by whiwho on 15/03/2020.
//

#ifndef TEMPGAMEMOTOR_GAME_MAP_H
#define TEMPGAMEMOTOR_GAME_MAP_H


#include <SDL_render.h>
#include <map>
#include "ECS/ECS.h"

class Game;
class GameMap {
private:
    int map_width, map_height;
    int** map;

    std::string file_name;
    std::map<std::string, SDL_Texture*> textures;
    SDL_Texture* water;

public:

    GameMap() = default;
    GameMap(int** map_t, int map_width_t, int map_height_t);
    GameMap(const char* map_sheet, Game *gApp);

    ~GameMap();


    void load_default_assets();

    void load_map(const char* map_sheet, Game *gApp);
    void print_map();
    void reshape_map();

    int get_map_width(){return map_width;}
    int get_map_height(){return map_height;}

};


#endif //TEMPGAMEMOTOR_GAME_MAP_H
