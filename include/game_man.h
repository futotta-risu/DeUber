#ifndef DEUBER_GAME_MAN_H
#define DEUBER_GAME_MAN_H

#include <algorithms/algorithm_helper.h>
#include <plog/Log.h>
#include <visual/components/car_component.h>
#include <visual/components/goal_component.h>
#include "ECS/Components/transform_component.h"
#include "maps/map.h"
#include "nlohmann/json.hpp"

class GameManager{
private:

    bool map_loaded = false;
    Map *mapa;
    generic_algorithm *alg;
    Game *gM;

public:
    GameManager(){
        mapa = nullptr;
    };
    ~GameManager(){
        delete mapa;
    }

    void set_game(Game *g){
        gM = g;
    }
    Game* get_game(){
        return gM;
    }
    void set_algorithm(algorithm_type alg_t){
        alg = get_algorithm_by_type(alg_t);
    }

    void load_map(const std::string& map_file_name){
        if(map_loaded)
            delete mapa;
        mapa = new Map();

        if(mapa!= nullptr) map_loaded = true;
        else return;

        mapa->read_map(map_file_name.c_str());
        seed_map_entities();
        PLOG_INFO << "Map loaded";
    }
    void seed_map_entities(){
        seed_map_tile_entities();
    }

    bool is_map_loaded(){
        return map_loaded;
    }

    void seed_map_tile_entities(){
        int **map_c = mapa->get_aval_map();
        for(int t(0); t < mapa->get_height(); t++){
            for(int r(0); r < mapa->get_width(); r++){
                Entity* temp_tile = nullptr;
                if(map_c[t][r]==0) temp_tile = &create_entity("tile-floor");
                else temp_tile = &create_entity("tile-building");

                dynamic_cast<TransformComponent*>(temp_tile->get_component(ComponentHelper::TRANSFORM))->set_pos(32*r,32*t);
            }
        }
    }

    void read_car_list(const char* car_list_file){
        std::vector<car> car_list = car::read_car_list_file(car_list_file);
        mapa->set_car_list(&car_list);
        for(int i = 0; i < mapa->get_car_list_size(); i++)
            add_car(mapa->get_car(i));
        PLOG_INFO << "Car list read";
    }

    void add_car(car* c){
        auto& new_car = create_entity("taxi");
        new_car.add_component(ComponentHelper::CARC);
        dynamic_cast<Car_component*>(new_car.get_component(ComponentHelper::CARC))->set_case(c, this->alg, this->mapa);
    }

    void print_car_list(){
        for(int i = 0; i <  mapa->get_car_list_size(); i++){
            auto c_temp = mapa->get_car(i);
            std::cout << "El coche " << i << " esta en : "<< c_temp->get_coord_x() << " : " << c_temp->get_coord_y() << std::endl;
        }
    }

    void add_random_goal(){
        int x_r, y_r, tries = 0;
        bool is_car = false;
        do{
            is_car = false;
            x_r = rand()%mapa->get_width();
            y_r = rand()%mapa->get_height();
            if(tries > 25) return;
            if(mapa->car_in_pos(x_r,y_r)) is_car=true;
        }while( mapa->get_cell(x_r, y_r)!=0  || mapa->check_goal(x_r,y_r) || is_car);
        Entity* new_goal;
        try{
             new_goal = &create_entity("goal");
        }catch(std::exception& e){
            // TODO Add error
            return;
        }
        new_goal->add_component(ComponentHelper::GOAL);
        dynamic_cast<goal_component*>(new_goal->get_component(ComponentHelper::GOAL))->set_case(mapa->add_goal(x_r, y_r));
        dynamic_cast<TransformComponent*>(new_goal->get_component(ComponentHelper::TRANSFORM))->set_pos(x_r*32, y_r*32);
    }

    Entity& create_entity(const std::string& ent_name){
        if(!gM->g_entities.count(ent_name)) throw std::exception();

        auto& temp_ent = gM->e_man.man.add_entity();
        temp_ent.add_group(G_PLAYER);
        G_Entity q = gM->g_entities[ent_name];
        for(std::pair<std::string, nlohmann::json> c_comp : q.get_ent_components())
            temp_ent.add_component(ComponentHelper::ComponentMapSCT[c_comp.first],&c_comp.second );


        return temp_ent;
    }
};

#endif //DEUBER_GAME_MAN_H
