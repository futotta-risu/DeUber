#ifndef WINDOW_MANAGER_SDL2_CONV_H
#define WINDOW_MANAGER_SDL2_CONV_H


#include <SDL_stdinc.h>

inline SDL_bool to_SDL_bool(bool b){
    return b ? SDL_TRUE : SDL_FALSE;
}


#endif //WINDOW_MANAGER_SDL2_CONV_H
