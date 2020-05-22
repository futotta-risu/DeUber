#include <meta/CDimension.h>

SDL_Rect d_to_R(Position p, Dimension d){
    SDL_Rect a = {p.x,p.y,d.w,d.h};
    return a;
}