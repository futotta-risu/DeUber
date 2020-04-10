#include <time.h>
#include <cstdlib>
#include <string>

#define SDL_MAIN_HANDLED

#include "menu.h"
#include "algorithms/algorithm_helper.h"
#include "running_menu.h"
#include "visual/visual_run_handler.h"


int main(int argc, char* argv[]) {
    bool visual = true;
    if (argc > 1) {
        char *visual_style = argv[1];
        if (static_cast<std::string>(visual_style) == "visual")
            visual = true;
        else if (static_cast<std::string>(visual_style) == "non_visual")
            visual = false;
        else{
            std::cout << "Error: El argumento introducido no es valido. Introduzca o bien 'visual' o 'non_visual" << std::endl;
            return EXIT_SUCCESS;
        }
    }
    srand(time(nullptr));

    if (visual){
        visual_run_handler vrh;
        vrh.load("ej3.map", BFS);
    }else{
        // First Step get the info menu to get the whole running_info data
        running_info run_inf = run_menu(menu_file);
        // Load the data
        Map mapa;
        mapa.read_map(run_inf.map_name);
        mapa.add_car(1,0);
        running_menu_launch(&mapa, get_algorithm_by_type(run_inf.alg_name));
    }
    return EXIT_SUCCESS;
}
