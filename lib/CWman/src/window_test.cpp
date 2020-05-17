//
// Created by whiwho on 24/03/2020.
//

#define SDL_MAIN_HANDLED

#include <CWindow.h>
#include <component/CTextBox.h>
#include <component/CScrollPanel.h>
#include <component/CBar.h>
#include "component/CButton.h"
#include "component/CLabel.h"

#include <string>

int main(){
    CWindow win;
    CPanel *pan = new CPanel();
    CScrollPanel *sp = new CScrollPanel();
    sp->set_size({500,500});
    for(int i = 0; i < 20; i++){
        pan->add(new CButton("Button " + std::to_string(i)));
    }
    sp->set_panel(pan);
    win.add(sp);
    win.init_window();
    win.~CWindow();
}

