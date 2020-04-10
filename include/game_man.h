//
// Created by whiwho on 08/04/2020.
//

#ifndef DEUBER_GAME_MAN_H
#define DEUBER_GAME_MAN_H



#include <algorithms/algorithm_helper.h>
#include "maps/map.h"

#include "visual/objects/goal_entity.h"
#include "visual/objects/car_entity.h"

class GameManager{
private:

    // Manager Metadata

    bool map_loaded;

    // Manager Values
    Map *mapa;
    generic_algorithm *alg;

    Game *gM;

public:
    GameManager(){
        mapa = nullptr;
    };

    void set_game(Game *g){
        gM = g;
    }
    Game* get_game(){
        return gM;
    }
    void set_algorith(algorithm_type alg_t){
        alg = get_algorithm_by_type(alg_t);
    }

    void load_map( const char* map_file_name){
        if(map_loaded)
            delete mapa;

        mapa = new Map();

        if(mapa!= nullptr) map_loaded = true;
        else return;

        mapa->read_map(map_file_name);

        // TODO Set different goal system
        const short n_goals = 3;
        for(int i = 0; i < n_goals; i++)
            add_random_goal();

    }

    void  read_car_list(const char* car_list_file){
        std::vector<car> car_list = car::read_car_list_file(car_list_file);
        mapa->set_car_list(&car_list);
        for(int i = 0; i < mapa->get_car_list_size(); i++)
            add_car(mapa->get_car(i));
    }

    void add_car(car* c){
        car_entity::add_player("taxi",gM, c, alg,  mapa);
    }

    void print_car_list(){
        for(int i = 0; i <  mapa->get_car_list_size(); i++){
            auto c_temp = mapa->get_car(i);
            std::cout << "El coche " << i << " esta en : "<< c_temp->get_coord_x() << " : " << c_temp->get_coord_y() << std::endl;
        }
    }

    void add_random_goal(){
        int x_r, y_r;
        do{
            x_r = rand()%mapa->get_width();
            y_r = rand()%mapa->get_height();
        }while(mapa->get_cell(x_r, y_r)!=0 || mapa->check_goal(x_r,y_r) || (x_r == y_r && x_r == 1));
        goal_entity::add_goal(mapa->add_goal(x_r,y_r),gM, y_r, x_r);
    }

};

#endif //DEUBER_GAME_MAN_H
