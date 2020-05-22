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
    CButton *lbl1 = new CButton("Cent");
    lbl1->set_size({300,50});
    lbl1->set_alignment(CText::alignment_v::CENTER);
    lbl1->set_alignment(CText::alignment_h::CENTER);
    CButton *lbl12 = new CButton("Right");
    lbl12->set_background(255,0,255,255);
    lbl12->set_size({300,50});
    lbl12->set_alignment(CText::alignment_h::RIGHT);
    lbl12->set_alignment(CText::alignment_v::BOTTOM);
    CButton *lbl2 = new CButton("Nada");
    lbl2->set_size({300,50});
    CTextBox *lbl3 = new CTextBox();
    lbl3->set_size({300,50});
    pan->add(lbl1);
    pan->add(lbl12);
    pan->add(lbl2);
    pan->add(lbl3);
    win.add(pan);
    win.init_window();
    win.~CWindow();
}

