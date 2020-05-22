#include <ctime>
#include <cstdlib>
#include <string>

#define SDL_MAIN_HANDLED

#include "menu.h"
#include "algorithms/algorithm_helper.h"
#include "running_menu.h"
#include <visual/main_menu.h>
#include <visual/login.h>

#include <plog/Log.h>

void start_non_visual_interface(){
    // First Step get the info menu to get the whole running_info data
    running_info run_inf = run_menu(menu_file);

    Map mapa;
    mapa.read_map(run_inf.map_name);
    mapa.add_car(1,0);
    running_menu_launch(&mapa, get_algorithm_by_type(run_inf.alg_name));
}

void start_visual_interface(){


    auto login_window = new Login();
    delete login_window;

    if(login_data==1){
        auto deUber = new DeUber();
        delete deUber;
    }
}


int main(int argc, char* argv[]) {
    plog::init(plog::debug, "logs/running.log");
    srand(time(nullptr));


    bool visual_interface = true;
    if (argc > 1)
        visual_interface = static_cast<std::string>(argv[1]) == "visual";

    if(visual_interface) start_visual_interface();
    else start_non_visual_interface();


    return EXIT_SUCCESS;
}
