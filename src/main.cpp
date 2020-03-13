#include "maps/map.h"
#include "util/file/config_handler.h"

#include "global.h"
#include "menu.h"
#include "algorithms/algorithm_helper.h"
#include "running_menu.h"


#include <iostream>

#include <stdio.h>
#include <string.h>
#include <time.h>

int car::car_id = 0;

int main(int argc, char **argv){
    srand(time(NULL));

    struct running_info run_inf = run_menu(menu_file);
    std::cout << "OLALLALALA\n";
    map mapa;
    std::cout << "OLALLALALA\n";
    mapa.read_map(run_inf.map_name);
    std::cout << "OLALLALALA\n";
    //mapa.write_map(map_write);
    mapa.add_car(2,2);
    mapa.add_car(1,1);
    std::cout << "OLALLALALA\n";
    running_menu_launch(&mapa, get_algorithm_by_type(run_inf.alg_name));


    return 0;
}
