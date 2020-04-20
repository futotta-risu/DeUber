//
// Created by erikberter on 21/03/2020.
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
    VerticalFlowLayout(int v_gap) : WindowLayout(),v_gap{v_gap},h_margin{10}{
        change_layout(WindowLayout::LayoutType::VERTICAL_FLOW);
    };
    void set_size(std::vector<CComponent*> component_list, CComponent* parent_panel) override;
};


#endif //WINDOWMANAGER_VERTICAL_FLOW_LAYOUT_H
