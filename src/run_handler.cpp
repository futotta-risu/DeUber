//
// Created by whiwho on 16/03/2020.
//

#include "../include/algorithms/algorithm_helper.h"
#include "../include/run_handler.h"
#include "../include/running_menu.h"
#include "visual/visual_run_handler.h"


run_handler::run_handler(bool visual_t){
    std::cout << "estado"<< visual_t << std::endl;
    visual = visual_t;
    if(visual) visual_handler();
    else non_visual_handler();
}

run_handler::~run_handler(){

}

void run_handler::non_visual_handler(){
    // First Step get the info menu to get the whole running_info data
    run_inf = run_menu(menu_file);

    // Load the data
    Map mapa;
    mapa.read_map(run_inf.map_name);

    mapa.add_car(1,0);
    running_menu_launch(&mapa, get_algorithm_by_type(run_inf.alg_name));
}


void run_handler::visual_handler(){
    std::cout << "Prueba " << 1 << std::endl;
    visual_run_handler vrh("ej2.map",BFS);
    std::cout << "Prueba " << 2 << std::endl;
    vrh.main_loop();
    std::cout << "Prueba " << 3 << std::endl;
}

