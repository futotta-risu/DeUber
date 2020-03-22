//
// Created by whiwho on 21/03/2020.
//

#ifndef WINDOWMANAGER_BORDER_LAYOUT_H
#define WINDOWMANAGER_BORDER_LAYOUT_H

#include "window_layout.h"

class BorderLayout : public WindowLayout {
private:
    int h_margin;
    int v_gap;
public:
    static enum Position{
        NORTH,SOUTH,EAST,WEST,CENTER
    };
    BorderLayout();
    void set_size(std::vector<WindowComponent*> component_list, SDL_Rect *coords) override;
};
#endif //WINDOWMANAGER_BORDER_LAYOUT_H
