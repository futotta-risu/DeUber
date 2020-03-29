//
// Created by whiwho on 14/03/2020.
//

#ifndef TEMPGAMEMOTOR_TEXTURE_MANAGER_H
#define TEMPGAMEMOTOR_TEXTURE_MANAGER_H

#include "SDL.h"
#include "SDL_Image.h"

#include "game.h"

class TextureManager{
public:
    static SDL_Texture* LoadTexture(SDL_Renderer** ren, const char* file_name);
    static void draw(SDL_Renderer** ren, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};

#endif //TEMPGAMEMOTOR_TEXTURE_MANAGER_H
