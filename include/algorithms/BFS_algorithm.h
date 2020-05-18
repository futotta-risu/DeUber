//
// Created by erikberter on 16/03/2020.
//

#ifndef DEUBER_BFS_ALGORITHM_H
#define DEUBER_BFS_ALGORITHM_H

#include <stack>
#include <iostream>

class BFS_algorithm : public generic_algorithm {
public:

    void check_pos(std::queue<std::pair<int,int> > *coord_list, std::pair<int,int> coords,
            int*** map, std::pair<int,int> *goal_coords, bool *reached, std::pair<int,int> map_size,
            std::pair<int,int> ant_pos){
        if(!(coords.first>=0 && coords.first<map_size.second && coords.second>=0 && coords.second<map_size.first))
            return;
        if((*map)[coords.second][coords.first]>3 || (*map)[coords.second][coords.first]==1) return;
        if((*map)[coords.second][coords.first]==3) {
            *goal_coords = std::make_pair(coords.first,coords.second);
            *reached=true;
            return;
        }
        (*map)[coords.second][coords.first]=(*map)[ant_pos.second][ant_pos.first]+1;
        (*coord_list).push(std::make_pair(coords.first,coords.second));

    }

    // val_back | dir
    void get_dir_val(int*** map, int dir, std::pair<int,int> pos, std::pair<int,int> map_size, std::pair<int,int> *vals){
        if(!(pos.first>=0 && pos.first<map_size.second && pos.second>=0 && pos.second<map_size.first))
            return;

        if((*map)[pos.second][pos.first]>3 && ((*map)[pos.second][pos.first]<vals->first || vals->first==-1)){
                vals->first = (*map)[pos.second][pos.first];
                vals->second = dir;
        }
    }

    int get_best_move(Map *map_t, car *car_t) override{
        if(car_t->get_operation() == WORKING)
            return car_t->get_move();
        int** map = map_t->get_aval_map();
        std::pair<int,int> map_size = std::make_pair(map_t->get_height(),map_t->get_width());

        bool goal_reached = false;
        int pos_x = car_t->get_coord_x();
        int pos_y = car_t->get_coord_y();

        std::queue<std::pair<int,int> > coord_list;
        coord_list.push(std::make_pair(pos_x,pos_y));
        std::pair<int,int> goal_coords;

        std::pair<int,int> first_coords = std::make_pair(pos_x,pos_y);


        map[pos_y][pos_x] = 5; // TODO Improve FIRST VAL

        while(!goal_reached && !coord_list.empty()){
            std::pair<int,int> act_coords = coord_list.front();
            coord_list.pop();
            check_pos(&coord_list, std::make_pair(act_coords.first-1,act_coords.second), &map,
                    &goal_coords,&goal_reached,map_size,act_coords);
            check_pos(&coord_list, std::make_pair(act_coords.first+1,act_coords.second), &map,
                    &goal_coords,&goal_reached,map_size,act_coords);
            check_pos(&coord_list, std::make_pair(act_coords.first,act_coords.second-1), &map,
                      &goal_coords,&goal_reached,map_size,act_coords);
            check_pos(&coord_list, std::make_pair(act_coords.first,act_coords.second+1), &map,
                      &goal_coords,&goal_reached,map_size,act_coords);
        }
        if(!goal_reached)
            return 0;

        std::pair<int,int> back_coords = goal_coords;
        int act_val_back = map[goal_coords.second][goal_coords.first];
        std::stack<int> move_list;
        while(map[back_coords.second][back_coords.first]!=5){
            std::pair<int,int> vals = std::make_pair(-1, -1);
            get_dir_val(&map, 4, std::make_pair(back_coords.first-1,back_coords.second), map_size, &vals);
            get_dir_val(&map, 1, std::make_pair(back_coords.first,back_coords.second+1), map_size, &vals);
            get_dir_val(&map, 2, std::make_pair(back_coords.first+1,back_coords.second), map_size, &vals);
            get_dir_val(&map, 3, std::make_pair(back_coords.first,back_coords.second-1), map_size, &vals);
            move_list.push(vals.second);
            back_coords.first += (((vals.second+1)%2==0) ? 0: ((vals.second == 2) ? 1 : -1));
            back_coords.second += (2*(vals.second%2)-((vals.second*vals.second*vals.second)%4));

        }
        while(!move_list.empty()){
            car_t->add_move(((move_list.top()+2)%4==0) ? 4 : (move_list.top()+2)%4);
            move_list.pop();
        }

        for(unsigned int i = 0; i < map_size.first; i++)
            delete[] map[i];
        delete[] map;

        if(car_t->get_operation() == WORKING)
            return car_t->get_move();
        return 0;
    };

    void move_cars(Map *map_t) override{
        for(int i = 0; i < map_t->get_car_list_size(); i++){
            car *car_t = map_t->get_car(i);
            int dir = get_best_move(map_t, car_t);
            car_t->dir = dir;
            map_t->move_car(car_t->get_id(),dir);
        }
    }

    void move_car(Map *map_t, car* act_car) override{
        int dir = get_best_move(map_t, act_car);
        act_car->dir = dir;
        map_t->move_car(act_car->get_id(),dir);
    }

    void reload(){

        
    }
private:
};

#endif //DEUBER_BFS_ALGORITHM_H
