#ifndef WINDOW_MANAGER_COLORS_H
#define WINDOW_MANAGER_COLORS_H

#include <SDL_types.h>
#include <SDL_pixels.h>
#include <algorithm>
#include <map>

enum CColor {BLACK, WHITE, GREY};

static std::map<CColor, SDL_Color*> color_map ={
        {BLACK, new SDL_Color({0  ,0  ,0  ,255})},
        {WHITE, new SDL_Color({255,255,255,255})},
        {GREY , new SDL_Color({233,233,233,255})}
};

inline SDL_Color get_color(CColor color_t){
    if ( color_map.find(color_t) == color_map.end() ) return *color_map[BLACK];
    else return *color_map[color_t];
}
inline Uint8 check_bound(int a){ return static_cast<Uint8>(std::max( 0, std::min(255, a)));}
inline Uint8 check_bound(Uint8 a){ return static_cast<Uint8>(std::max( 0, std::min(255, static_cast<int>(a))));}



inline static SDL_Color int_to_SDL_Color(int r, int g, int b, int a){
    return SDL_Color({check_bound(r),check_bound(g),check_bound(b),check_bound(a)});
}

inline static SDL_Color SDL_Color_dsp(SDL_Color color, int dsp){
    return int_to_SDL_Color(static_cast<int>(color.r)+dsp,static_cast<int>(color.g)+dsp,
            static_cast<int>(color.b)+dsp,static_cast<int>(color.a));
}
#endif //WINDOW_MANAGER_COLORS_H
