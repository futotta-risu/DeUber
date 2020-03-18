//
// Created by whiwho on 10/03/2020.
//

#ifndef DEUBER_RUNNING_MENU_H
#define DEUBER_RUNNING_MENU_H


#include "algorithms/generic_algorithm.h"
#include "maps/map.h"

typedef struct {
  bool is_animated = false;
  int animated_fps = 5;
} running_menu_data;


void running_menu_launch(map *mapa, generic_algorithm *algorithm);
void run_program(map *mapa, generic_algorithm *algorithm, running_menu_data run_dat);
running_menu_data config_running_menu_type();

#endif //DEUBER_RUNNING_MENU_H
