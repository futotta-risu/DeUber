#include <time.h>
#include <cstdlib>
#include <string>


#define SDL_MAIN_HANDLED

#include "menu.h"
#include "algorithms/algorithm_helper.h"
#include "running_menu.h"
#include "visual/visual_run_handler.h"
#include <visual/map_selector.h>
#include <plog/Log.h>

int main(int argc, char* argv[]) {
    plog::init(plog::debug, "logs/running.log");
    PLOG_INFO << "Starting Program";
    bool visual = true;
    if (argc > 1) {
        char *visual_style = argv[1];
        if (static_cast<std::string>(visual_style) == "visual")
            visual = true;
        else if (static_cast<std::string>(visual_style) == "non_visual")
            visual = false;
        else{
            PLOG_ERROR << "Invalid command line argument introduced";
            std::cout << "Error: El argumento introducido no es valido. Introduzca o bien 'visual' o 'non_visual" << std::endl;
            return EXIT_SUCCESS;
        }
    }
    srand(time(nullptr));
    if (visual){
        PLOG_INFO << "Starting visual mode.";
        visual_run_handler vrh;
        std::string map_name;
        do{
            PLOG_INFO << "Selecting a Map. ";
            auto *t = new MapSelector(&map_name,"../data/maps/");
            t->~MapSelector();
            PLOG_INFO << "Selected map: " << map_name;
        }while(map_name.empty());
        vrh.load(map_name.c_str(), BFS);
    }else{
        PLOG_INFO << "Starting non visual mode.";
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
