//
// Created by erikberter on 20/03/2020.
//

#ifndef WINDOWMANAGER_WINDOW_LAYOUT_H
#define WINDOWMANAGER_WINDOW_LAYOUT_H

#include <vector>
#include "component/window_component.h"
#include "SDL.h"

class WindowLayout{
private:
public:
    virtual void set_size( std::vector<WindowComponent*> component_list, SDL_Rect *coords) = 0;
};

#endif //WINDOWMANAGER_WINDOW_LAYOUT_H
