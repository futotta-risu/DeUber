//
// Created by erikberter on 18/03/2020.
//

#ifndef DEUBER_TEXTURE_MANAGER_H
#define DEUBER_TEXTURE_MANAGER_H

#include <SDL.h>


class TextureManager{
public :
    static SDL_Renderer **ren;
    static SDL_Texture* LoadTexture(const char* file_name);
    static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};

#endif //DEUBER_TEXTURE_MANAGER_H
