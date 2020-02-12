//
// Created by whiwho on 12/02/2020.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../../src/maps/map.h"



TEST_CASE( "Map check Height ", "[map]" ) {
    map map1(2,3);
    REQUIRE( map1.get_height() == 2 );
}

TEST_CASE("Map check Width" ,"[map]"){
    map map1(2,3);
    REQUIRE( map1.get_width() == 3 );
}
