//
// Created by whiwho on 11/02/2020.
//

#include <assert.h>
#include "map.h"

map::map(){
    n_height = 0;
    n_width = 0;
    map_values = nullptr;

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
}

void map::reshape(int width, int height){
    // TODO Mejorar los errores
    if(width < 0)
        throw "Negative Width"; // Un mapa no puede tener tamaño negativo
    else if(width > MAX_MAP_WIDTH)
        throw "Excesive Width";
    if(height < 0)
        throw "Negative height"; // Un mapa no puede tener tamaño negativo
    else if(height > MAX_MAP_HEIGHT)
        throw "Excesive height";

    map_values = new int*[height];
    for(unsigned int i = 0; i < height; i++)
        map_values[i] = new int[width];

}

std::string map::print_map(){
    std::string temp_result = "";
    for(unsigned int i_height = 0; i_height < n_height; i_height){
        for(unsigned int i_width = 0; i_width < n_width; i_width)
            temp_result += (char)  map_values[i_height][i_width];
        temp_result += "\n";
    }
    return temp_result;
}

map::~map() {
    for(unsigned int i = 0; i < n_height; i++)
        delete[] map_values[i];
    delete[] map_values;
}
