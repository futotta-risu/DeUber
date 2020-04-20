//
// Created by whiwho on 24/03/2020.
//

#define SDL_MAIN_HANDLED

#include <CWindow.h>
#include <component/CTextBox.h>
#include <component/CToggleButton.h>
#include <component/CBar.h>
#include <component/CScrollPanel.h>
#include "component/CButton.h"
#include "component/CLabel.h"
#include "SDL.h"

/*
int main(){
    CWindow win;
    win.set_layout(new BorderLayout());
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
    but->set_action_listener([](CWindow* win) {
        CComponent *textbox =  win->get_component_by_id("txt");
        CComponent *tbl =  win->get_component_by_id("tbl");
        if(textbox== nullptr || tbl == nullptr) std::cout << "No se ha encontrado" << std::endl;{
            if(dynamic_cast<CToggleButton*>(tbl)->get_state())
                std::cout << "El valor es :" << dynamic_cast<CTextBox*>(textbox)->get_text() << std::endl;
            else std::cout << "Apretao" << std::endl;
        }
    });
    but->set_window(&win);
    g_pan->add(but);
    g_pan->add(tbl);
    g_pan->add(pan);
    CButton *but3 = new CButton("Pr33ueba2");
    win.add(g_pan, BorderLayout::BLPosition::EAST);
    win.add(but3, BorderLayout::BLPosition::WEST);
    CBar *bar = new CBar();
    win.add(bar);
    win.init_window();
    win.~CWindow();
}
*/
int main(){
    CWindow win;
    CScrollPanel *pann = new CScrollPanel;
    pann->set_size({400,500});
    CPanel *g_pan = new CPanel();
    g_pan->set_background({0,255,0,0});
    g_pan->add(new CLabel("Label"));
    pann->set_panel(g_pan);
    g_pan->add(new CLabel("Gola1"));
    g_pan->add(new CLabel("Gola2"));
    g_pan->add(new CLabel("Gola10"));
    g_pan->add(new CLabel("Gola11"));
    g_pan->add(new CLabel("Gola12"));
    g_pan->add(new CLabel("Gola13"));
    g_pan->add(new CLabel("Gola14"));
    g_pan->add(new CLabel("Gola15"));
    g_pan->add(new CLabel("Gola16"));
    g_pan->add(new CLabel("Gola17"));
    g_pan->add(new CLabel("Gola18"));
    g_pan->add(new CLabel("Gola19"));

    win.add(pann);
    win.init_window();
    win.~CWindow();
}

