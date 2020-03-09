#include "maps/map.h"
#include "util/file/config_handler.h"

#include "global.h"
#include "menu.h"
#include "algorithms/random_algorithm.h"
#include <iostream>

int car::car_id = 0;

int main(int argc, char **argv ) {

    //struct running_info run_inf = run_menu(menu_file);
    //printf("Hemos salido\n\n");
    //printf("Mapa: %s :: Alg :: %i", run_inf.map_name, run_inf.alg_name);
    map mapa;
    mapa.read_map(map_file);
    mapa.print_map();
    //mapa.write_map(map_write);
    std::cout << "The car id" << car::car_id << std::endl;
    mapa.add_car(2,2);
    mapa.add_car(1,1);
    std::cout << "The car id" << car::car_id << std::endl;
    mapa.print_map();
    std::cout << "The car id---------" << car::car_id << std::endl;
    random_algorithm alg;
    alg.move_cars(&mapa);
    std::cout << "The car id---------" << car::car_id << std::endl;
    mapa.print_map();


    return 0;
}
