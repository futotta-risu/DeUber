#ifndef WINDOW_MANAGER_FLOWLAYOUT_H
#define WINDOW_MANAGER_FLOWLAYOUT_H
#include "WindowLayout.h"

class FlowLayout : public WindowLayout {
private:
    int v_margin;
    int h_gap;
public:
    FlowLayout();
    FlowLayout(int h_gap) : WindowLayout(),h_gap{h_gap},v_margin{10}{
        change_layout(WindowLayout::LayoutType::VERTICAL_FLOW);
    };
    void set_size(std::vector<CComponent*> component_list, CComponent* parent_panel) override;
};

#endif //WINDOW_MANAGER_FLOWLAYOUT_H
