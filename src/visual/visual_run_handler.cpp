//
// Created by whiwho on 18/03/2020.
//


#include "visual_run_handler.h"

#include "visual/ECS/objects/car_entity.h"
#include "visual/ECS/objects/tile_entity.h"
#include "visual/ECS/objects/goal_entity.h"

#include "../algorithms/algorithm_helper.h"

SDL_Renderer *visual_run_handler::ren;
SDL_Event visual_run_handler::event;
EntityManager visual_run_handler::ent_man;
Asset_manager visual_run_handler::ast_man;
std::vector<Collision_component*> visual_run_handler::colliders;


visual_run_handler::visual_run_handler(std::string map_file_name, algorithm_type alg_t){

    SDL_Init(0);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGH, 0, &win, &ren);
    SDL_SetWindowTitle(win, "DeUber");

    run_dat = {true, 20};
    std::cout << " sdas " << std::endl;
    mapa = Map();
    mapa.read_map(map_file_name.c_str());
    int **map_copy = mapa.get_aval_map();
    std::vector<std::pair<int,int> > goal_coords;
    for(int i = 0; i < mapa.get_height(); i++)
        for(int j = 0; j < mapa.get_width(); j++){
            if(map_copy[i][j]>1){
                if(map_copy[i][j]==3)
                    goal_entity::add_goal("goal",mapa.add_goal(j,i), i, j);
                goal_coords.emplace_back(std::make_pair(i,j));
                map_copy[i][j]=0;
            }
            tile_entity::add_tile("tile", map_copy[i][j], i, j);
        }

    alg_type = alg_t;
    algorithm = get_algorithm_by_type(alg_type);
    ast_man.load_default();

    // TODO optimizar en tema de memoria
    car_list = car::read_car_list_file("../data/cars/car_list1.txt");
    mapa.set_car_list(&car_list);
    for(auto& c : car_list)
        car_entity::add_player("taxi", &c);
}

visual_run_handler::~visual_run_handler(){
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void visual_run_handler::main_loop(){
    is_running = true;
    unsigned int last_frame;
    counter = 0;
    while(is_running){

        last_frame = SDL_GetTicks();
        input();
        update();
        render();

        unsigned int timer_fps = SDL_GetTicks()-last_frame;

        if(timer_fps < static_cast<int>(1000/run_dat.animated_fps))
            SDL_Delay(static_cast<int>(1000/run_dat.animated_fps)-timer_fps);
        counter++;
    }
}

void visual_run_handler::input(){
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }
}

void visual_run_handler::update(){
    if(counter%15==0){
        std::cout << "Pruena 1" << std::endl;
        algorithm->move_cars(&mapa);
    }

    ent_man.update();
}

void visual_run_handler::render(){
    SDL_RenderClear(ren);
    ent_man.draw();
    SDL_RenderPresent(ren);
}