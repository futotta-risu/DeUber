//
// Created by whiwho on 18/03/2020.
//

#ifndef DEUBER_ASSET_MANAGER_H
#define DEUBER_ASSET_MANAGER_H

#include <SDL.h>
#include <map>
#include "ECS.h"
#include "animation.h"

class Asset_manager{
private:

    Manager*man;
    std::map<std::string, SDL_Texture*> texture_map;
    std::map<std::string, std::map<std::string, Animation> > texture_anim_map;
public:

    Asset_manager(){};
    Asset_manager(Manager* man);
    ~Asset_manager();

    void load_default();

    void add_texture(std::string id, const char* path);
    SDL_Texture* get_texture(std::string id);

    void add_animation(std::string id, const char* path);
    std::map<std::string, Animation> get_animation_map(std::string id);

};

#endif //DEUBER_ASSET_MANAGER_H
