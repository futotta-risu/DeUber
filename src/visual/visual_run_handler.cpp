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
    auto gApp = new GameApp(window->get_render(), map_file_name.c_str());
    auto but = new CButton("Otro boton guay");

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
    for(int i = 0; i < mapa.get_height(); i++){
        for(int j = 0; j < mapa.get_width(); j++){
            if(map_copy[i][j]>1){
                if(map_copy[i][j]==3)
                    goal_entity::add_goal(mapa.add_goal(j,i),gApp->g, i, j);
                map_copy[i][j]=0;
            }

        }
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


