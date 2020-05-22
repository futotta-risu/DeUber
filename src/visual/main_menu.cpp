#include <component/CButton.h>
#include <renderer.h>

#include "visual/main_menu.h"
#include "visual/game_component.h"

#include "visual/map_selector.h"

#include "algorithms/algorithm_helper.h"

#include <plog/Log.h>
#include <visual/components/car_component.h>
#include <ECS/Components/component_helper_t.h>
#include <visual/components/goal_component.h>
#include <layout/FlowLayout.h>

DeUber::DeUber() : CWindow("DeUber") {
    _set_default_window_properties();
    _load_game_components();
    _load_top_menu();
    _load_GameApp();
    add(gApp, BorderLayout::BLPosition::CENTER);

    init_window();
}

void DeUber::_set_default_window_properties(){
    set_size(WIDTH, HEIGHT);
    set_layout(new BorderLayout());
    set_resizable(false);
}

void DeUber::_load_game_components(){
    GameRender::ren = *get_render();
    gApp = new GameApp();

    add_new_component_meta(ComponentHelper::CARC,"carc",
            []() -> Car_component* {return new Car_component;});
    add_new_component_meta(ComponentHelper::GOAL,"goal",
            []() -> goal_component* {return new goal_component;});
}

void DeUber::_load_GameApp(){
    gApp->load();

    gApp->gm->set_algorithm(algorithm_type::BFS);
    gApp->gm->get_game()->e_man.add_to_order(G_CAR);
    gApp->set_id("GAPP");

}

void DeUber::_set_pause_action(){
    pause->set_action_listener([&](CWindow* win){
        GameApp *gAppC =  dynamic_cast<GameApp*>(win->get_component_by_id("GAPP"));
        CButton *pauseButton =  dynamic_cast<CButton*>(win->get_component_by_id("PauseButton"));

        if(gAppC== nullptr){PLOG_ERROR << "No se ha encontrado el componente GameApp.";return;}
        gAppC->set_paused();
        pauseButton->set_text(
                pauseButtonText[(int) gAppC->is_paused()]);
    });
}
void DeUber::_set_load_map_action(){
    load_map->set_action_listener([&](CWindow* win){
        std::string map_name_t;
        MapSelector t(&map_name_t, "../data/maps/");

        if(map_name_t.empty()) return;

        gApp->reset();
        _load_GameApp();
        gApp->gm->load_map(map_name_t);
        gApp->gm->read_car_list("../data/cars/car_list1.txt");
    });
}

void DeUber::_set_button_properties(CButton *btn){
    btn->set_window(this);
    btn->set_size({100,50});
    btn->set_minimum_size({100,50});
    btn->set_border_size(0);
    btn->set_background(155,183,181,255);
}

void DeUber::_set_top_bar_properties(){
    top_bar->set_layout(new FlowLayout(0,0));
    top_bar->set_size(50,600);
    top_bar->set_minimum_size({600,50});
    top_bar->set_background(155,183,181,255);
    top_bar->set_border_size(0);
}

void DeUber::_load_top_menu(){
    top_bar = new CPanel();
    _set_top_bar_properties();

    pause = new CButton("Pause");
    pause->set_id("PauseButton");
    _set_pause_action();
    _set_button_properties(pause);

    load_map = new CButton("Load Map");
    _set_load_map_action();
    _set_button_properties(load_map);

    top_bar->add(pause);
    top_bar->add(load_map);
    add(top_bar, BorderLayout::BLPosition::NORTH);
}

