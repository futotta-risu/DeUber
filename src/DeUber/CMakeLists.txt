cmake_minimum_required(VERSION 3.15)
project(DeUber)

set(CMAKE_CXX_STANDARD 14)



add_executable(DeUber src/main.cpp src/maps/map.cpp src/maps/map.h src/cars/car.cpp src/cars/car.h src/util/ds/string_graph.c src/util/ds/string_graph.h src/menu.c src/util/file/file_reader.c src/util/strings/strings_c.c src/util/strings/strings_c.h)

set(TEST_FOLDER tests)
include_directories(${TEST_FOLDER}/include)
add_executable(DeUberTest ${TEST_FOLDER}/maps/map_test.cpp src/maps/map.cpp)

