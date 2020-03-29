//
// Created by whiwho on 14/03/2020.
//

#include "texture_manager.h"
#include <fstream>

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer** ren, const char* file_name){
    std::ifstream f(file_name);

    if(!f){
        std::cout << file_name << std::endl;
        std::cout << "Not opened" << std::endl;
        return nullptr;
    }

    SDL_Surface* surf = IMG_Load(file_name);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(*ren,surf);
    SDL_FreeSurface(surf);
    return tex;
}
void TextureManager::draw(SDL_Renderer** ren, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(*ren, tex,&src,&dest);
}