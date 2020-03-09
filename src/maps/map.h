//
// Created by whiwho on 11/02/2020.
//

#ifndef DEUBER_MAP_H
#define DEUBER_MAP_H

#include <string>
#include <vector>
#include "car.h"

const int MAX_MAP_WIDTH = 20000;
const int MAX_MAP_HEIGHT = 20000;

enum cell_type {
    FLOOR = 0, BUILDING = 1, CAR = 2, GOAL = 3
};

struct cell_char{
    cell_type def_val;
    cell_type act_val;
};

class map {
private:
    cell_char** map_values;
    std::vector<car> car_list;
protected:
    int n_width, n_height;
public:
    map();
    map(int height, int width);
    map(cell_char** map_values, int height, int width) :
        map_values{map_values}, n_width{width}, n_height{height}{
        car_list = {};
    };
    ~map();

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

    void move_car(int id, int dir);

    int get_car_list_size(){
        return car_list.size();
    }
    car get_car(int i){
        return car_list[i];
    }
};


#endif //DEUBER_MAP_H
