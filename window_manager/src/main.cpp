#include <iostream>

#include "window_handler.h"
#include "component/component_list.h"
#include "layout/vertical_flow_layout.h"

int main() {
    WindowHandler win;
    ComponentButton button("Hola me llamo erik");
    CPanel* pan = new CPanel();
    pan->set_background_color({230,0,0,255});
    pan->add(new ComponentButton("Button2"));
    pan->add(new ComponentButton("Button2"));
    pan->add(new ComponentButton("Button2"));
    pan->add(new ComponentButton("Button2"));
    win.add(pan);
    win.add(&button);

    win.set_layout(new VerticalFlowLayout(10));
    win.init_window();
    return 0;
}
