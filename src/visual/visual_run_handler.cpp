//
// Created by erikberter on 18/03/2020.
//

#include <component/CButton.h>
#include <renderer.h>

#include "visual/visual_run_handler.h"
#include "visual/game_component.h"

#include "algorithms/algorithm_helper.h"

#include <plog/Log.h>
#include <visual/components/car_component.h>
#include <ECS/Components/component_helper_t.h>
#include <visual/components/goal_component.h>

#define G_CAR 25

CWindow& create_window(){
    auto window = new CWindow("DeUber");
    window->set_size(WIDTH, HEIGHT);
    return *window;
}

void load_game_components(){
    add_new_component_meta(ComponentHelper::CARC,
                           "carc", []() -> Car_component* {return new Car_component;});
    add_new_component_meta(ComponentHelper::GOAL,
                           "goal", []() -> goal_component* {return new goal_component;});
}

void load_GameApp(GameApp* gApp, const std::string& map_file_name){
    gApp->load();

    gApp->gm->load_map(map_file_name.c_str());
    gApp->gm->set_algorithm(algorithm_type::BFS);
    gApp->gm->read_car_list("../data/cars/car_list1.txt");
    gApp->gm->get_game()->e_man.add_to_order(G_CAR);
    gApp->set_id("GAPP");

}

void load_pause_button(CWindow& win){
    auto but = new CButton("Pause");
    but->set_action_listener(
            [](CWindow *win){
                CComponent *gAppC =  win->get_component_by_id("GAPP");
                if(gAppC== nullptr) PLOG_ERROR << "No se ha encontrado el componente GameApp.";
                else dynamic_cast<GameApp*>(gAppC)->set_paused();
            }
    );

    but->set_window(&win);
    win.add(but);
}

void start_visual_interface(const std::string& map_file_name){
    auto& window = create_window();
    GameRender::ren = *window.get_render();

    load_game_components();
    auto gApp = new GameApp();

    load_pause_button(window);
    load_GameApp(gApp,  map_file_name);
    window.add(gApp);

    window.init_window();
    window.~CWindow();
}
