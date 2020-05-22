#define SDL_MAIN_HANDLED

#include <CWindow.h>
#include <component/CButton.h>
#include <component/CScrollPanel.h>
#include <string>

int main(){
    CWindow win;
    CScrollPanel *scp = new CScrollPanel();
    scp->set_minimum_size({400,400});
    CPanel *pan = new CPanel();
    pan->set_minimum_size({400,400});
    for(int i = 0; i< 20; i++){
        pan->add(new CButton("ADASD"));
    }
    scp->set_panel(pan);
    win.add(scp);
    win.init_window();
    win.~CWindow();
}

