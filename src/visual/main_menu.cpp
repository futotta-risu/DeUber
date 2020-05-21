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

#define G_CAR 25

const char* pauseButtonText[2] = {"Pause", "Play"};


DeUber::DeUber() : CWindow("DeUber") {
    set_default_window();
    GameRender::ren = *get_render();
    load_game_components();

    gApp = new GameApp();

    load_top_buttons();
    load_GameApp();

    add(gApp, BorderLayout::BLPosition::CENTER);

    init_window();
}
void DeUber::set_default_window(){
    set_size(WIDTH, HEIGHT);
    set_layout(new BorderLayout());
}

void DeUber::load_game_components(){
    add_new_component_meta(ComponentHelper::CARC,
                           "carc", []() -> Car_component* {return new Car_component;});
    add_new_component_meta(ComponentHelper::GOAL,
                           "goal", []() -> goal_component* {return new goal_component;});
}

void DeUber::load_GameApp(){
    gApp->load();

    gApp->gm->set_algorithm(algorithm_type::BFS);
    gApp->gm->get_game()->e_man.add_to_order(G_CAR);
    gApp->set_id("GAPP");

}

void DeUber::load_top_buttons(){
    auto top_bar = new CPanel();
    top_bar->set_layout(new FlowLayout);
    auto but = new CButton("Pause");
    but->set_id("PauseButton");
    but->set_action_listener(
            [&](CWindow* win){
                GameApp *gAppC =  dynamic_cast<GameApp*>(win->get_component_by_id("GAPP"));
                CButton *pauseButton =  dynamic_cast<CButton*>(win->get_component_by_id("PauseButton"));

                if(gAppC== nullptr){PLOG_ERROR << "No se ha encontrado el componente GameApp.";return;}
                gAppC->set_paused();
                pauseButton->set_text(
                        pauseButtonText[(int) gAppC->is_paused()]);

            }
    );

    but->set_window(this);
    top_bar->add(but);
    auto load_map = new CButton("Load Map");
    auto map_name = new std::string;
    load_map->set_action_listener([&, map_name](CWindow* win){
        do{
            std::string map_name_t;
            MapSelector t(&map_name_t, "../data/maps/");
            *map_name = map_name_t;
        }while(map_name->empty());
        gApp->reset();
        gApp->load();
        gApp->gm->set_algorithm(algorithm_type::BFS);
        gApp->gm->get_game()->e_man.add_to_order(G_CAR);
        gApp->gm->load_map(*map_name);
        gApp->gm->read_car_list("../data/cars/car_list1.txt");
    });
    load_map->set_window(this);
    top_bar->add(load_map);
    add(top_bar, BorderLayout::BLPosition::NORTH);
}

