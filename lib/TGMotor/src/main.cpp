#define SDL_MAIN_HANDLED
#include "SDL.h"

#include <iostream>

#include <renderer.h>
#include "game.h"

int main(int argc, char* argv[]){

    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS)==-1)) {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    }

    SDL_Window *win = SDL_CreateWindow("DEF",100,100,700,400,0);
    GameRender::ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    Game *g = new Game("../data/.config");

    g->load_defs({});
    g->set_stage("stage1");

    g->main_loop();


    SDL_DestroyRenderer(GameRender::ren);
    SDL_DestroyWindow(win);
    SDL_QuitSubSystem(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
    SDL_Quit();

    return 0;
}