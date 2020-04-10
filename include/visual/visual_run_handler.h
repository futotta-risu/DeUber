//
// Created by erikberter on 18/03/2020.
//

#ifndef DEUBER_VISUAL_RUN_HANDLER_H
#define DEUBER_VISUAL_RUN_HANDLER_H


#include "algorithms/algorithm_type.h"
#include "algorithms/generic_algorithm.h"

#include "maps/map.h"

#include "SDL.h"
#include "SDL_image.h"

#include "running_info.h"

#include "CWindow.h"


const int WIDTH = 800, HEIGHT = 600;

class visual_run_handler {
private:
    CWindow* window;

public:
    std::vector<car> car_list;

    generic_algorithm *algorithm;

    running_menu_data run_dat;

    visual_run_handler();
    ~visual_run_handler() = default;

    void load(const char* map_file_name, algorithm_type alg_t);

};


#endif //DEUBER_VISUAL_RUN_HANDLER_H
