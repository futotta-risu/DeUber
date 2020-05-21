#ifndef WINDOWMANAGER_WINDOW_LAYOUT_H
#define WINDOWMANAGER_WINDOW_LAYOUT_H

#include <vector>
#include "CComponent.h"
#include "SDL.h"

class WindowLayout{
private:
public:
    enum LayoutType{
        NONE, BORDER, ABSOLUTE, VERTICAL_FLOW, FLOW, SCROLLBAR
    };
    LayoutType layout_type = NONE;
    void change_layout(LayoutType layout_type_t){
        layout_type = layout_type_t;
    }
    LayoutType get_layout_type(){
        return layout_type;
    }
    virtual void set_size(std::vector<CComponent*> component_list, CComponent* parent_panel) = 0;
};

#endif //WINDOWMANAGER_WINDOW_LAYOUT_H
