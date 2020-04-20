//
// Created by whiwho on 18/03/2020.
//

#include "ECS/asset_manager.h"
#include "texture_manager.h"
#include <fstream>
#include <utils/files.h>

#include "g_constants.h"



void AssetManager::load_resources(SDL_Renderer* ren, const std::string& path){


    std::string regex_png_t = constants::ASSET_REGEX_PNG;
    std::string regex_lst_t = constants::ASSET_REGEX_LST;
    sp_str::functional_vector vc;

    sp_str::function_v_ss function_png = [ren, this](const std::string& a, const std::string& b){
        this->add_texture(ren,a, b.c_str());
    };
    sp_str::function_v_ss function_lst = [this](const std::string& a, const std::string& b){
        this->add_animation(a,b.c_str());
    };
    vc.push_back(std::make_pair(regex_png_t, function_png));
    vc.push_back(std::make_pair(regex_lst_t, function_lst));

    file_rec(path, vc);
}

void AssetManager::add_texture(SDL_Renderer* tex, const std::string& id, const char* path){
    // TODO Add To Log
    //std::cout << "Adding texture " << path <<std::endl;
    texture_map.emplace(id, TextureManager::LoadTexture(tex, path));
}
SDL_Texture* AssetManager::get_texture(const std::string& id){
    return texture_map[id];
}

void AssetManager::add_animation(const std::string& id, const char* path){
    // TODO Add To Log
    // std::cout << "Adding animation " << path <<std::endl;
    std::map<std::string, Animation> temp_a;
    std::ifstream asset_list_f(path);

    int n_asset;
    asset_list_f >> n_asset;
    std::string anim_id;
    int anim_f;
    for(int i = 0; i < n_asset; i++){
        asset_list_f >> anim_id >> anim_f;
        temp_a[anim_id]  = Animation(i,anim_f,100);
    }
    texture_anim_map[id] = temp_a;
}

std::map<std::string, Animation> AssetManager::get_animation_map(std::string& id){
    return texture_anim_map[id];
}