#define SDL_MAIN_HANDLED

#include <CWindow.h>
#include <component/CTextBox.h>
#include <component/CScrollPanel.h>
#include <component/CTextBox.h>
#include "component/CButton.h"
#include "component/CLabel.h"

#include <string>
#include <layout/VerticalFlowLayout.h>

int main(){
    CWindow win;
    CPanel *pan = new CPanel();
    VerticalFlowLayout *flow = new VerticalFlowLayout();
    pan->set_layout(flow);
    CButton *lbl1 = new CButton("Bn");
    lbl1->set_size({300,50});
    CLabel *lbl2 = new CLabel("Bnasd");
    lbl2->set_size({300,50});
    CTextBox *lbl3 = new CTextBox();
    lbl3->set_size({300,50});
    pan->add(lbl1);
    pan->add(lbl2);
    pan->add(lbl3);
    win.add(pan);
    win.init_window();
    win.~CWindow();
}

