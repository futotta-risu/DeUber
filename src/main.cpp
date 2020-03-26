
#include <time.h>
#include <cstdlib>

#define SDL_MAIN_HANDLED
#include "../include/run_handler.h"

#include "window_handler.h"
#include "component/component_button.h"

#include <functional>

int main(int argc, char* argv[]){
    bool visual = true;
    if(argc > 1){
        char* visual_style = argv[1];
        std::cout << static_cast<std::string>(visual_style) << std::endl;
        if(static_cast<std::string>(visual_style) == "visual")
            visual = true;
        else if(static_cast<std::string>(visual_style) == "non_visual")
            visual = false;
    }

    std::cout << visual << std::endl;

    srand(time(NULL));

    run_handler launcher(visual);
    /*
    WindowHandler win("Titulo de prueba", 600,800);
    */
    return EXIT_SUCCESS;
}
