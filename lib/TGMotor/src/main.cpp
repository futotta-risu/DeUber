#include <iostream>
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "game.h"


int main(int argc, char* argv[]){

    Game g;
    g.main_loop();
    return 0;
}