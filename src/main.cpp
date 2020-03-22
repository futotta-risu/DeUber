
#include <time.h>
#include <cstdlib>

#define SDL_MAIN_HANDLED
#include "../include/run_handler.h"

#include "window_handler.h"
#include "component/component_button.h"

#include <functional>

int main(int argc, char* argv[]){
    bool visual = false;
    if(argc > 0){
        char* visual_style = argv[1];
        std::cout << static_cast<std::string>(visual_style) << std::endl;
        if(static_cast<std::string>(visual_style) == "visual")
            visual = true;
    }

    srand(time(NULL));

    run_handler launcher(visual);
    /*
    WindowHandler win("Titulo de prueba", 600,800);
    CPanel* pan = new CPanel();
    pan->set_background_color({255,0,0});
    pan->add(new ComponentButton("Pruebas2"));
    pan->add(new ComponentButton("Pruebas3"));
    pan->add(new ComponentButton("Pruebas4"));
    win.add(pan);
    ComponentButton* but = new ComponentButton("Otro boton guay");
    std::function<void(int)> f = [](int ){};

    but->set_action_listener(
            [](void ){
                std::cout << "Pruebaaas" << std::endl;
            }
            );
    win.add(but);
    win.init_window();*/
    return EXIT_SUCCESS;
}
