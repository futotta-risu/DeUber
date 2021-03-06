//
// Created by erikberter on 16/03/2020.
//
#include "maps/car.h"

#include <fstream>

int car::car_id = 0;
std::vector<car> car::read_car_list_file(const char* file_path){

    std::ifstream f(file_path);
    int n_lines;
    f >> n_lines;
    std::vector<car> car_list;
    for(int i = 0; i < n_lines; i++){
        int x,y;
        f >> x >> y;
        car_list.emplace_back(car(x,y));
    }
    f.close();
    return car_list;
}