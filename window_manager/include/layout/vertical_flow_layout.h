//
// Created by whiwho on 21/03/2020.
//

#ifndef WINDOWMANAGER_VERTICAL_FLOW_LAYOUT_H
#define WINDOWMANAGER_VERTICAL_FLOW_LAYOUT_H

#include "window_layout.h"

class VerticalFlowLayout : public WindowLayout {
private:
    int h_margin;
    int v_gap;
public:
    VerticalFlowLayout();
    VerticalFlowLayout(int v_gap) : WindowLayout(),v_gap{v_gap},h_margin{10}{};
    void set_size(std::vector<WindowComponent*> component_list, SDL_Rect *coords) override;
};


#endif //WINDOWMANAGER_VERTICAL_FLOW_LAYOUT_H
