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
#include "game_component.h"


const int WIDTH = 800, HEIGHT = 600;

CWindow& create_window();
void load_game_components();
void load_GameApp(GameApp* gApp, const std::string& map_file_name);
void load_pause_button(CWindow& win);

void start_visual_interface(const std::string& map_file_name);

#endif //DEUBER_VISUAL_RUN_HANDLER_H
