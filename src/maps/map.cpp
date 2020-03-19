//
// Created by whiwho on 11/02/2020.
//


#include <cstring>
#include <iostream>
#include <fstream>
#include "util/strings/strings_c.h"
#include "map.h"
#include "map_errors.h"
using namespace std;

Map::Map(){
    n_height = 0;
    n_width = 0;
    map_values = nullptr;
    car_list = {};
}

Map::Map(int height, int width) {
    n_height = height;
    n_width = width;
    try{
        reshape(n_height,n_width);
    }catch(std::exception e){
        map_values = nullptr;
    }
    car_list = {};
}

void Map::reshape(int height, int width){
    // TODO Mejorar los errores

    if(width < 0 || width > MAX_MAP_WIDTH || height < 0 || height > MAX_MAP_HEIGHT)
        throw map_out_of_bounds(width, height);

    n_width = width;
    n_height = height;
    map_values = new cell_char*[height];
    for(unsigned int i = 0; i < height; i++)
        map_values[i] = new cell_char[width];

}

void Map::print_map(){
    for(unsigned int i_height = 0; i_height < n_height; i_height++){
        for(unsigned int i_width = 0; i_width < n_width; i_width++){
            if(map_values[i_height][i_width].act_val == 0) printf("%c" , ' ');
            else printf("%i",map_values[i_height][i_width].act_val);
        }

        printf("\n");
    }
}

Map::~Map() {
    for(unsigned int i = 0; i < n_height; i++)
        delete[] map_values[i];
    delete[] map_values;
}

void Map::read_map(const char* file_name){
    char file_name_t[] = "../data/maps/";
    char* full_file_name = strcat(file_name_t, file_name);

    FILE *fptr = fopen(full_file_name, "r");

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
                car_list->push_back(car_t);
            }else if(map_values[temp_height][i].act_val == GOAL)
                map_values[temp_height][i].def_val = FLOOR;
        }

        temp_height++;
    }
}


void Map::write_map(const char* file_name){
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

void Map::add_car(int pos_x, int pos_y){

    if(!check_coords(pos_x, pos_y))
        throw invalid_coords(pos_x, pos_y, this);

    car car_temp(pos_x, pos_y);
    car_list->push_back(car_temp);

    map_values[pos_y][pos_x].act_val = CAR;
}
Goal* Map::add_goal(int pos_x, int pos_y){
    if(!check_coords(pos_x, pos_y))
        throw invalid_coords(pos_x, pos_y, this);
    if(goal_list.count(pos_y*n_height+pos_x)){
        goal_list[pos_y*n_height+pos_x]->active = true;
    }else{
        Goal* goal_t  = new Goal();
        goal_list[pos_y*n_height+pos_x] = goal_t;
    }

    map_values[pos_y][pos_x].act_val = GOAL;
    return goal_list[pos_y*n_height+pos_x];
}
void Map::delete_goal(int pos_x, int pos_y){
    goal_list[pos_y*n_height+pos_x]->destroy();
    map_values[pos_y][pos_x].act_val =  map_values[pos_y][pos_x].def_val;
}

void Map::add_car(car car_t){
    car_list->push_back(car_t);
    if(!check_coords(car_t.get_coord_x(), car_t.get_coord_y()))
        throw invalid_coords(car_t.get_coord_x(), car_t.get_coord_y(), this);

    map_values[car_t.get_coord_y()][car_t.get_coord_x()].act_val = CAR;
}

void Map::move_car(int id, int dir){
    if(dir==0) return;
    int index_of_car = -1;
    for(int i = 0; i < car_list->size(); i++)
        if((*car_list)[i].get_id() == id) {
            index_of_car = i;
            break;
        }
    if(index_of_car==-1) return;
    int val_y = (*car_list)[index_of_car].get_coord_y();
    int val_x = (*car_list)[index_of_car].get_coord_x();

    int val_y_n = val_y + (2*(dir%2)-((dir*dir*dir)%4));
    int val_x_n = val_x + (((dir+1)%2==0) ? 0: ((dir == 2) ? 1 : -1));


    if(map_values[val_y_n][val_x_n].def_val == BUILDING || map_values[val_y_n][val_x_n].act_val==CAR){
        (*car_list)[index_of_car].dir = 0;
        (*car_list)[index_of_car].set_operation(NONE);
        return;
    }
    if(map_values[val_y_n][val_x_n].act_val == GOAL)
        clear_cell(val_x_n,val_y_n);

    map_values[val_y][val_x].act_val = map_values[val_y][val_x].def_val;
    map_values[val_y_n][val_x_n].act_val = CAR;
    (*car_list)[index_of_car].set_coords(val_x_n,val_y_n);

}

int** Map::get_aval_map(){
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
bool Map::check_coords(int x, int y){
    if(x<0 || x>= this->n_width)
        throw invalid_coords(x,y,this);
    if(y<0 || y>= this->n_height)
        throw invalid_coords(x,y,this);
    return true;
}

