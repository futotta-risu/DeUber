#include "CMouse.h"

int CMouse::mouse_x=0,
    CMouse::mouse_y=0;

void CMouse::getMouseCoords(){
    SDL_GetMouseState(&CMouse::mouse_x, &CMouse::mouse_y);
}

bool CMouse::isClickLeft() {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT);
}

bool CMouse::isClickRight() {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT);
}