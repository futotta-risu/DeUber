cmake_minimum_required(VERSION 3.15)
project(DeUber)

set(CMAKE_CXX_STANDARD 14)



add_executable(DeUber src/main.cpp src/maps/map.cpp src/maps/map.h src/cars/car.cpp src/cars/car.h )

set(TEST_FOLDER tests)
include_directories(${TEST_FOLDER}/include)
add_executable(DeUberTest ${TEST_FOLDER}/maps/map_test.cpp)

