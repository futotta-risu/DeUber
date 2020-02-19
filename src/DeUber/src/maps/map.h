//
// Created by whiwho on 11/02/2020.
//

#ifndef DEUBER_MAP_H
#define DEUBER_MAP_H

#include <string>

const int MAX_MAP_WIDTH = 20000;
const int MAX_MAP_HEIGHT = 20000;

enum cell_type {
    FLOOR = 0, BUILDING = 1, CAR = 2
};

class map {
private:
    int** map_values;
protected:
    int n_width, n_height;
public:
    map();
    map(int height, int width);
    map(int** map_values, int height, int width) :
        map_values{map_values}, n_width{width}, n_height{height}{};
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
};


#endif //DEUBER_MAP_H
