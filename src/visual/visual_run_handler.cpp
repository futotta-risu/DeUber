//
// Created by erikberter on 18/03/2020.
//

#include <component/CButton.h>
#include "visual/visual_run_handler.h"

#include "visual/objects/car_entity.h"
#include "visual/objects/tile_entity.h"
#include "visual/objects/goal_entity.h"

#include "algorithms/algorithm_helper.h"

#include "game_component.h"


visual_run_handler::visual_run_handler(std::string& map_file_name, algorithm_type alg_t){
    window = new CWindow("DeUber");
    window->set_size(WIDTH, HEIGHT);
    window->init_SDL(0);
    auto gApp = new GameApp();
    gApp->load(window->get_render(), map_file_name.c_str());
    auto but = new CButton("Mapa");

    but->set_action_listener(
            [](){
                std::cout << "Pruebaaas" << std::endl;
            }
    );
    window->add(but);


    run_dat = {true, 20};
    Map mapa;
    mapa.read_map(map_file_name.c_str());
    int **map_copy = mapa.get_aval_map();
    const short n_goals = 3;
    for(int i = 0; i < n_goals; i++){
        int x_r, y_r;
        do{
            x_r = rand()%mapa.get_width();
            y_r = rand()%mapa.get_height();
        }while(map_copy[y_r][x_r]!=0 || mapa.check_goal(x_r,y_r) || (x_r == y_r && x_r == 1));
        goal_entity::add_goal(mapa.add_goal(x_r,y_r),gApp->g, y_r, x_r);
    }
    alg_type = alg_t;
    algorithm = get_algorithm_by_type(alg_type);

    // TODO optimizar en tema de memoria
    car_list = car::read_car_list_file("../data/cars/car_list1.txt");
    mapa.set_car_list(&car_list);
    for(auto& c : car_list)
        car_entity::add_player("taxi",gApp->g, &c, algorithm,  &mapa);
    //gApp->set_id("GAPP");
    std::vector<std::size_t> order_t = {G_TILES, G_ENEMY,G_PLAYER,G_COLLIDER,25};
    gApp->g->e_man.add_to_order(order_t);
    window->add(gApp);
    window->init_window();
}


