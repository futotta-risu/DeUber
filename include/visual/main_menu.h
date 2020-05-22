#ifndef DEUBER_MAIN_MENU_H
#define DEUBER_MAIN_MENU_H

#include "algorithms/algorithm_type.h"
#include "algorithms/generic_algorithm.h"
#include "maps/map.h"

#include <SDL.h>

#include <CWindow.h>
#include <component/CButton.h>
#include "game_component.h"

#define G_CAR 25

static const char* pauseButtonText[2] = {"Pause", "Play"};

const int WIDTH = 600, HEIGHT = 600;

class DeUber : public CWindow{
private:
    CPanel *top_bar;
    CButton *load_map, *pause;

    GameApp *gApp;


    void _set_default_window_properties();
    void _load_game_components();
    void _load_GameApp();
    void _load_top_menu();

    void _set_pause_action();
    void _set_load_map_action();

    void _set_button_properties(CButton *btn);
    void _set_top_bar_properties();
public:
    DeUber();

};





#endif //DEUBER_MAIN_MENU_H
