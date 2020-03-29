//
// Created by whiwho on 18/03/2020.
//

#include "ECS/asset_manager.h"
#include "texture_manager.h"
#include <fstream>

void AssetManager::load_default(SDL_Renderer** ren){

    std::ifstream asset_list_f("../res/assets/asset_list");
    int n_asset;
    asset_list_f >> n_asset;
    std::string asset_id;
    for(int i = 0; i < n_asset; i++){
        asset_list_f >> asset_id;
        add_texture(ren, asset_id, ("../res/assets/"+asset_id + ".png").c_str());
        add_animation(asset_id, ("../res/assets/"+asset_id + ".lst").c_str());
    }
    asset_list_f.close();

}

void AssetManager::add_texture(SDL_Renderer** tex, std::string id, const char* path){
    texture_map.emplace(id, TextureManager::LoadTexture(tex, path));
}
SDL_Texture* AssetManager::get_texture(std::string id){
    return texture_map[id];
}

void AssetManager::add_animation(std::string& id, const char* path){
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

std::map<std::string, Animation> AssetManager::get_animation_map(std::string& id){
    return texture_anim_map[id];
}