//
// Created by whiwho on 18/03/2020.
//


#include "ECS/asset_manager.h"
#include "texture_manager.h"
#include "ECS/animation.h"
#include <fstream>

Asset_manager::Asset_manager(Manager* man) :  man{man}{}
Asset_manager::~Asset_manager(){}

void Asset_manager::load_default(){

    std::ifstream asset_list_f("../res/visual/asset_list");
    int n_asset;
    asset_list_f >> n_asset;
    std::string asset_id;
    for(int i = 0; i < n_asset; i++){
        asset_list_f >> asset_id;
        add_texture(asset_id, ("../res/visual/assets/"+asset_id + ".png").c_str());
        add_animation(asset_id, ("../res/visual/assets/"+asset_id + ".lst").c_str());
    }
    asset_list_f.close();

}

void Asset_manager::add_texture(std::string id, const char* path){
    texture_map.emplace(id, TextureManager::LoadTexture(path));
}
SDL_Texture* Asset_manager::get_texture(std::string id){
    return texture_map[id];
}

void Asset_manager::add_animation(std::string id, const char* path){
    std::map<std::string, Animation> temp_a;
    std::ifstream asset_list_f(path);

    int n_asset;
    asset_list_f >> n_asset;
    std::string anim_id;
    int anim_f;
    for(int i = 0; i < n_asset; i++){
        asset_list_f >> anim_id >> anim_f;
        temp_a[anim_id.c_str()]  = Animation(i,anim_f,100);
    }
    texture_anim_map[id] = temp_a;
}

std::map<std::string, Animation> Asset_manager::get_animation_map(std::string id){
    return texture_anim_map[id];
}