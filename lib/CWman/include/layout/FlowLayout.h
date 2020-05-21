#ifndef WINDOW_MANAGER_FLOWLAYOUT_H
#define WINDOW_MANAGER_FLOWLAYOUT_H
#include "WindowLayout.h"

class FlowLayout : public WindowLayout {
private:
    int v_margin;
    int h_gap;
public:
    FlowLayout();
    FlowLayout(int h_gap, int v_margin) : WindowLayout(),h_gap{h_gap},v_margin{v_margin}{
        change_layout(WindowLayout::LayoutType::VERTICAL_FLOW);
    };

    void set_v_margin(int v_margin_t){v_margin = v_margin_t;};
    void set_h_gap(int h_gap_t){h_gap = h_gap_t;};
    void set_size(std::vector<CComponent*> component_list, CComponent* parent_panel) override;
};

#endif //WINDOW_MANAGER_FLOWLAYOUT_H
