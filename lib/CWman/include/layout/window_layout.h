//
// Created by erikberter on 20/03/2020.
//

#ifndef WINDOWMANAGER_WINDOW_LAYOUT_H
#define WINDOWMANAGER_WINDOW_LAYOUT_H

#include <vector>
#include "CComponent.h"
#include "SDL.h"

class WindowLayout{
private:
public:
    virtual void set_size(std::vector<CComponent*> component_list, CComponent* parent_panel) = 0;
};

#endif //WINDOWMANAGER_WINDOW_LAYOUT_H
