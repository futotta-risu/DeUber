#ifndef DEUBER_MAIN_MENU_H
#define DEUBER_MAIN_MENU_H

#include "algorithms/algorithm_type.h"
#include "algorithms/generic_algorithm.h"
#include "maps/map.h"

#include "SDL.h"
#include "SDL_image.h"

#include "running_info.h"

#include "CWindow.h"
#include "game_component.h"

const int WIDTH = 800, HEIGHT = 600;

class DeUber : public CWindow{
private:
    GameApp *gApp;
public:
    DeUber();

    void set_default_window();

    void load_game_components();

    void load_GameApp();
    void load_top_buttons();

};





#endif //DEUBER_MAIN_MENU_H
