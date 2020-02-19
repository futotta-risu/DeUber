//
// Created by whiwho on 11/02/2020.
//

#include <assert.h>
#include <stdlib.h>
#include <cstring>
#include "util/strings/strings_c.h"
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
    map_values = new int*[height];
    for(unsigned int i = 0; i < height; i++)
        map_values[i] = new int[width];

}

void map::print_map(){
    for(unsigned int i_height = 0; i_height < n_height; i_height++){
        for(unsigned int i_width = 0; i_width < n_width; i_width++)
            printf("%i",map_values[i_height][i_width]);
        printf("\n");
    }
}

map::~map() {
    for(unsigned int i = 0; i < n_height; i++)
        delete[] map_values[i];
    delete[] map_values;
}

void map::read_map(const char* file_name){
    FILE *fptr = fopen(file_name, "r");
    assert(fptr != NULL);

    size_t line_s;
    char * buffer = NULL;

    line_s = getline(&buffer, &line_s, fptr);

    int map_width  = atoi(trim(strtok(buffer, " ")));
    int map_height = atoi(trim(strtok(NULL, " ")));

    reshape(map_width, map_height);
    int temp_height = 0;
    while ((line_s = getline(&buffer, &line_s, fptr)) != -1) {
        for(int i = 0; i < map_width; i++)
            map_values[temp_height][i] = buffer[i] -'0';
        temp_height++;
    }
}