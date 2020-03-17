//
// Created by whiwho on 16/03/2020.
//

#include "algorithms/algorithm_helper.h"
#include "software_launcher.h"
#include "running_menu.h"


bool software_launcher::visual = false;

void software_launcher::main_launch(){
    if(software_launcher::visual) visual_handler();
    else non_visual_handler();

}

void software_launcher::non_visual_handler(){
    // First Step get the info menu to get the whole running_info data
    run_inf = run_menu(menu_file);

    // Load the data
    map mapa;
    mapa.read_map(run_inf.map_name);

    mapa.add_car(1,0);
    running_menu_launch(&mapa, get_algorithm_by_type(run_inf.alg_name));
}


void software_launcher::visual_handler(){



}