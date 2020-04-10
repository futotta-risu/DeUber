//
// Created by whiwho on 18/03/2020.
//

#ifndef TEMPGAMEMOTOR_ASSET_MANAGER_H
#define TEMPGAMEMOTOR_ASSET_MANAGER_H


#include <map>
#include "ECS.h"
#include <SDL.h>
#include "animation.h"

class AssetManager {

    std::map<std::string, SDL_Texture*> texture_map;
    std::map<std::string, std::map<std::string, Animation> > texture_anim_map;
public:

    AssetManager() = default;
    ~AssetManager() = default;

    void load_default(SDL_Renderer** ren);

    void add_texture(SDL_Renderer** tex, std::string id, const char* path);
    SDL_Texture* get_texture(std::string id);

    void add_animation(std::string& id, const char* path);
    std::map<std::string, Animation> get_animation_map(std::string& id);
};


#endif //TEMPGAMEMOTOR_ASSET_MANAGER_H