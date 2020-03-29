//
// Created by whiwho on 28/03/2020.
//

#ifndef DEUBER_FRAMEVISUALIZATOR_H
#define DEUBER_FRAMEVISUALIZATOR_H

#include "GameVisualizator.h"

#include "SDL.h"

const int WIDTH = 800, HEIGH = 600;

class FrameVisualizator : public GameVisualizator{

private:

    SDL_Window* win;
    SDL_Renderer* ren;
public:
    FrameVisualizator() : GameVisualizator() {init();};
    ~FrameVisualizator(){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
    };

    virtual void init(){
        SDL_Init(0);
        SDL_CreateWindowAndRenderer(WIDTH, HEIGH, 0, &win, &ren);
        SDL_SetWindowTitle(win, "Eralia");
    };
    virtual void draw(std::vector<Entity> draw_c){
        for(auto& c : draw_c)
            c.draw();
    };

    virtual SDL_Renderer** get_renderer(){
        return &ren;
    };
};
#endif //DEUBER_FRAMEVISUALIZATOR_H
