//
// Created by whiwho on 11/02/2020.
//

#include <assert.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include "util/strings/strings_c.h"
#include "map.h"
using namespace std;

map::map(){
    n_height = 0;
    n_width = 0;
    map_values = nullptr;
    car_list = {};
    assert(map_values == nullptr);
}

map::map(int height, int width) {
    n_height = height;
    n_width = width;
    try{
        reshape(n_height,n_width);
    }catch(std::exception e){
        map_values = nullptr;
    }
    car_list = {};
}

void map::reshape(int height, int width){
    // TODO Mejorar los errores
    if(width < 0)
        throw "Negative Width"; // Un mapa no puede tener tamaño negativo
    else if(width > MAX_MAP_WIDTH)
        throw "Excesive Width";
    if(height < 0)
        throw "Negative height"; // Un mapa no puede tener tamaño negativo
    else if(height > MAX_MAP_HEIGHT)
        throw "Excesive height";

    n_width = width;
    n_height = height;
    map_values = new cell_char*[height];
    for(unsigned int i = 0; i < height; i++)
        map_values[i] = new cell_char[width];

}

void map::print_map(){
    for(unsigned int i_height = 0; i_height < n_height; i_height++){
        for(unsigned int i_width = 0; i_width < n_width; i_width++){
            if(map_values[i_height][i_width].act_val == 0) printf("%c" , ' ');
            else printf("%i",map_values[i_height][i_width].act_val);
        }

        printf("\n");
    }
}

map::~map() {
    for(unsigned int i = 0; i < n_height; i++)
        delete[] map_values[i];
    delete[] map_values;
}

void map::read_map(const char* file_name){
    char file_name_t[] = "../data/maps/";
    char* full_file_name = strcat(file_name_t, file_name);

    FILE *fptr = fopen(full_file_name, "r");
    assert(fptr != NULL);

    size_t line_s;
    char * buffer = NULL;

    line_s = getline(&buffer, &line_s, fptr);

    int map_width  = atoi(trim(strtok(buffer, " ")));
    int map_height = atoi(trim(strtok(NULL, " ")));

    reshape(map_width, map_height);
    int temp_height = 0;
    while ((line_s = getline(&buffer, &line_s, fptr)) != -1) {
        for(int i = 0; i < map_width; i++){
            map_values[temp_height][i].act_val = static_cast<cell_type>(buffer[i] -'0');
            map_values[temp_height][i].def_val = static_cast<const cell_type>(buffer[i] -'0');
            if(map_values[temp_height][i].act_val == CAR){
                map_values[temp_height][i].def_val = FLOOR;
                car car_t(i,temp_height);
                car_list.push_back(car_t);
            }

        }

        temp_height++;
    }
}


void map::write_map(const char* file_name){
    ofstream myfile;
    cout << file_name <<endl;
    myfile.open (file_name);
    myfile << n_width << " " << n_height << endl;
    for(unsigned int i_height = 0; i_height < n_height; i_height++) {
        for (unsigned int i_width = 0; i_width < n_width; i_width++)
            myfile << map_values[i_height][i_width].act_val;
        myfile << "\n";
    }
    myfile.close();
}

void map::add_car(int pos_x, int pos_y){
    // TODO check if valid coords
    car car_temp(pos_x, pos_y);
    car_list.push_back(car_temp);

    map_values[pos_y][pos_x].act_val = CAR;
}
void map::add_car(car car_t){
    // TODO check if correct coords
    car_list.push_back(car_t);

    map_values[car_t.get_coord_y()][car_t.get_coord_x()].act_val = CAR;
}

void map::move_car(int id, int dir){
    if(dir==0) return;
    int index_of_car = -1;
    for(int i = 0; i < car_list.size(); i++)
        if(car_list[i].get_id() == id) {
            index_of_car = i;
            break;
        }
    if(index_of_car==-1) return;
    int val_y = car_list[index_of_car].get_coord_y();
    int val_x = car_list[index_of_car].get_coord_x();

    int val_y_n = val_y + (2*(dir%2)-((dir*dir*dir)%4));
    int val_x_n = val_x + (((dir+1)%2==0) ? 0: ((dir == 2) ? 1 : -1));

    if(val_x_n<0 || val_x_n>= this->n_width) return;
    if(val_y_n<0 || val_y_n>= this->n_height) return;
    if(map_values[val_y_n][val_x_n].def_val != 0 || map_values[val_y_n][val_x_n].act_val==CAR) return;

    map_values[val_y][val_x].act_val = map_values[val_y][val_x].def_val;
    map_values[val_y_n][val_x_n].act_val = CAR;
    car_list[index_of_car].set_coords(val_x_n,val_y_n);

}

int** map::get_aval_map(){
    int** map_copy = new int*[n_height];
    for(unsigned int i = 0; i < n_height; i++){
        map_copy[i] = new int[n_width];
        for(unsigned int j = 0; j < n_width; j++){
            if(map_values[i][j].act_val==FLOOR) map_copy[i][j] = 0;
            else if(map_values[i][j].act_val==CAR) map_copy[i][j] = 0;
            else if(map_values[i][j].act_val==BUILDING) map_copy[i][j] = 1;
            else map_copy[i][j] = 3;
        }
    }


    return map_copy;
}
