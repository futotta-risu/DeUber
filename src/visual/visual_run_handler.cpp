//
// Created by erikberter on 18/03/2020.
//

#include <component/CButton.h>

#include "visual/visual_run_handler.h"

#include "algorithms/algorithm_helper.h"

#include "visual/game_component.h"
#include "game_man.h"


visual_run_handler::visual_run_handler(){}


void visual_run_handler::load(const char* map_file_name, algorithm_type alg_t){


    window = new CWindow("DeUber");
    window->set_size(WIDTH, HEIGHT);

    GameApp *gApp = new GameApp();
    gApp->load(window->get_render(), map_file_name);

    gApp->gm->load_map(map_file_name);
    gApp->gm->set_algorith(alg_t);

    auto but = new CButton("Mapa");


    but->set_action_listener(
            [](CWindow *win){
                CComponent *gAppC =  win->get_component_by_id("GAPP");

                if(gAppC== nullptr) std::cout << "No se ha encontrado" << std::endl;
                dynamic_cast<GameApp*>(gAppC)->set_paused();
            }
    );
    but->set_window(window);
    window->add(but);

    run_dat = {true, 20};
    algorithm = get_algorithm_by_type(alg_t);

    gApp->gm->read_car_list("../data/cars/car_list1.txt");
    gApp->gm->print_car_list();

    gApp->set_id("GAPP");
    std::vector<std::size_t> order_t = {G_TILES, G_ENEMY,G_PLAYER,G_COLLIDER,25};
    gApp->gm->get_game()->e_man.add_to_order(order_t);
    window->add(gApp);
    window->init_window();
}

void load_game(){

}
