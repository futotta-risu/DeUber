//
// Created by erikberter on 11/02/2020.
//

#ifndef DEUBER_MAP_H
#define DEUBER_MAP_H

#include <string>
#include <vector>
#include <map>

#include "car.h"
#include "goal.h"

const int MAX_MAP_WIDTH = 20000;
const int MAX_MAP_HEIGHT = 20000;



enum cell_type {
    FLOOR = 0, BUILDING = 1, CAR = 2, GOAL = 3
};

struct cell_char{
    cell_type def_val;
    cell_type act_val;
};

class Map {
private:
    cell_char** map_values;
    std::vector<car>* car_list;
    std::map<int, Goal*> goal_list;
protected:
    int n_width, n_height;
public:
    Map();
    Map(int height, int width);
    Map(cell_char** map_values, int height, int width) :
        map_values{map_values}, n_width{width}, n_height{height}{
        car_list = new std::vector<car>();
    };
    ~Map();

    // Getters and Setters

    int get_width(){
        return n_width;
    }
    int get_height(){
        return n_height;
    }

    // Operators

    // Other Functions
    void reshape(int height, int width);
    void print_map();

    void read_map(const char* file_name);

    void write_map(const char *file_name);

    void add_car(int pos_x, int pos_y);
    void add_car(car car_t);

    Goal* add_goal(int pos_x, int pos_y);
    bool check_goal(int pos_x, int pos_y);
    void delete_goal(int pos_x, int pos_y);
    void move_car(int id, int dir);

    int** get_aval_map();

    int get_car_list_size(){
        return car_list->size();
    }
    car *get_car(int i){
        return &(*car_list)[i];
    }

    void set_car_list(std::vector<car> *car_list_t){
        car_list = car_list_t;
    }

    bool check_coords(int x, int y);
    void clear_cell(int pos_x, int pos_y){
        goal_list[pos_y*n_height+pos_x]->destroy();
        map_values[pos_y][pos_x].act_val = FLOOR;
    }

};


#endif //DEUBER_MAP_H
