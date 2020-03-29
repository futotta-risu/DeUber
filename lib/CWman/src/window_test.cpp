//
// Created by whiwho on 24/03/2020.
//

#define SDL_MAIN_HANDLED

#include <CWindow.h>
#include <component/CTextBox.h>
#include <component/CToggleButton.h>
#include "component/CButton.h"
#include "component/CLabel.h"

int main(){
    static CWindow win;
    CPanel *pan = new CPanel();
    CPanel *g_pan = new CPanel();
    g_pan->set_background({0,255,0,0});
    CTextBox *xtb = new CTextBox();
    CToggleButton *tbl = new CToggleButton("Toglg");
    tbl->set_id("tbl");
    xtb->set_size({300,40});
    xtb->set_id("txt");
    pan->add(xtb);
    pan->set_background({255,0,0,0});
    g_pan->add(new CLabel("Eto es label"));
    CButton *but = new CButton("Prueba2");
    but->set_action_listener([]() {
        CComponent *textbox =  win.get_component_by_id("txt");
        CComponent *tbl =  win.get_component_by_id("tbl");
        if(textbox== nullptr || tbl == nullptr) std::cout << "No se ha encontrado" << std::endl;
        {
            if(dynamic_cast<CToggleButton*>(tbl)->get_state())
                std::cout << "El valor es :" << dynamic_cast<CTextBox*>(textbox)->get_text() << std::endl;
            else std::cout << "Apretao" << std::endl;


        }
    });
    g_pan->add(but);
    g_pan->add(tbl);
    g_pan->add(pan);
    win.add(g_pan);
    win.init_window();
}