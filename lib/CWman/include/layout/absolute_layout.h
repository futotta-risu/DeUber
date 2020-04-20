//
// Created by erikberter on 20/03/2020.
//

#ifndef WINDOWMANAGER_ABSOLUTE_LAYOUT_H
#define WINDOWMANAGER_ABSOLUTE_LAYOUT_H

#include "window_layout.h"

class AbsoluteLayout : public WindowLayout{

public:
    AbsoluteLayout(){
        change_layout(WindowLayout::LayoutType::ABSOLUTE);
    }
    void set_size(std::vector<CComponent*> component_list, CComponent* parent_panel) override;
};
#endif //WINDOWMANAGER_ABSOLUTE_LAYOUT_H
