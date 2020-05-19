//
// Created by erikberter on 21/03/2020.
//

#ifndef WINDOWMANAGER_BORDER_LAYOUT_H
#define WINDOWMANAGER_BORDER_LAYOUT_H

#include "WindowLayout.h"
#include "CComponent.h"
class BorderLayout : public WindowLayout {
private:
    int h_margin;
    int v_gap;

    // NORTH, SOUTH, EAST, WEST, CENTER
    CComponent *comps[5];
public:

    enum BLPosition{
        NORTH=0,SOUTH=1,EAST=2,WEST=3,CENTER=4
    };


    BorderLayout();
    void set_comp(CComponent* comp, BLPosition p){
        comps[static_cast<int>(p)] = comp;
    };
    void set_size(std::vector<CComponent*> component_list, CComponent* parent_panel) override;
};
#endif //WINDOWMANAGER_BORDER_LAYOUT_H
