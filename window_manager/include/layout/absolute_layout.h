//
// Created by whiwho on 20/03/2020.
//

#ifndef WINDOWMANAGER_ABSOLUTE_LAYOUT_H
#define WINDOWMANAGER_ABSOLUTE_LAYOUT_H

#include "window_layout.h"

class AbsoluteLayout : public WindowLayout{

public:
    void set_size(std::vector<WindowComponent*> component_list, SDL_Rect *coords) override;
};
#endif //WINDOWMANAGER_ABSOLUTE_LAYOUT_H
