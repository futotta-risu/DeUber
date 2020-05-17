#ifndef WINDOW_MANAGER_CMOUSE_H
#define WINDOW_MANAGER_CMOUSE_H
#include <SDL.h>

namespace CMouse {
    extern int mouse_x, mouse_y;

    void getMouseCoords();

    bool isClickLeft();
    bool isClickRight();
}
#endif //WINDOW_MANAGER_CMOUSE_H
