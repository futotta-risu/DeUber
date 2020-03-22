//
// Created by erikberter on 18/03/2020.
//


#include <component/component_list.h>
#include "visual/visual_run_handler.h"

#include "visual/objects/car_entity.h"
#include "visual/objects/tile_entity.h"
#include "visual/objects/goal_entity.h"

#include "algorithms/algorithm_helper.h"

#include "game_component.h"


visual_run_handler::visual_run_handler(std::string& map_file_name, algorithm_type alg_t){

    window = WindowHandler("DeUber", HEIGHT, WIDTH);
    window.init_SDL(0);
    TextureManager::ren = &window.ren;
    auto gApp = new GameApp();
    gApp->ast_man.load_default();
    auto pan = new CPanel();
    pan->set_background_color({255,0,0});
    pan->add(new ComponentButton("Pruebas2"));
    pan->add(new ComponentButton("Pruebas3"));
    pan->add(new ComponentButton("Pruebas4"));
    window.add(pan);

    auto but = new ComponentButton("Otro boton guay");

    but->set_action_listener(
            [](){
                std::cout << "Pruebaaas" << std::endl;
            }
    );
    window.add(but);


    run_dat = {true, 20};

    Map mapa;
    mapa.read_map(map_file_name.c_str());
    int **map_copy = mapa.get_aval_map();
    std::vector<std::pair<int,int> > goal_coords;
    for(int i = 0; i < mapa.get_height(); i++)
        for(int j = 0; j < mapa.get_width(); j++){
            if(map_copy[i][j]>1){
                if(map_copy[i][j]==3)
                    goal_entity::add_goal(mapa.add_goal(j,i),gApp, i, j);
                goal_coords.emplace_back(std::make_pair(i,j));
                map_copy[i][j]=0;
            }
            tile_entity::add_tile("tile", gApp, map_copy[i][j], i, j);
        }

    alg_type = alg_t;
    algorithm = get_algorithm_by_type(alg_type);


    // TODO optimizar en tema de memoria
    car_list = car::read_car_list_file("../data/cars/car_list1.txt");
    mapa.set_car_list(&car_list);
    for(auto& c : car_list)
        car_entity::add_player("taxi",gApp, &c, algorithm,  &mapa);
    //gApp->set_id("GAPP");
    window.add(gApp);
    window.init_window();
}


