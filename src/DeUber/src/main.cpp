#include <iostream>
#include "maps/map.h"

int main() {


    int** map_pruebas = new int*[3];

    map_pruebas[1] = new int[3];
    map_pruebas[2] = new int[3];

    for(int i = 0 ; i < 3;i++){
        map_pruebas[i] = new int[3];
        for(int j = 0; j < 3; j++)
            map_pruebas[i][j] = (i+j)%2;
    }

    map mapa(map_pruebas,3,3);
    std::cout << mapa.print_map();

    return 0;
}
