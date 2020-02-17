//
// Created by whiwho on 12/02/2020.
//



#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../../src/maps/map.h"

TEST_CASE("Map creation", "[map]"){
    int** map_pruebas = new int*[3];

    map_pruebas[1] = new int[3];
    map_pruebas[2] = new int[3];

    for(int i = 0 ; i < 3;i++){
        map_pruebas[i] = new int[3];
        for(int j = 0; j < 3; j++)
            map_pruebas[i][j] = (i+j)%2;
    }

    map mapa(map_pruebas,3,3);
    mapa.print_map();
}

TEST_CASE( "Map check Height ", "[map]" ) {

    map map1(2,3);

    REQUIRE( map1.get_height() == 2 );
}

TEST_CASE("Map check Width" ,"[map]"){
    map map1(2,3);
    REQUIRE( map1.get_width() == 3 );
}
