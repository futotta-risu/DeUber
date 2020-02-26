cmake_minimum_required(VERSION 3.15)
project(DeUber)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories(src/maps src/cars src/util/ds src/util/file src/util/strings src)
add_executable(DeUber src/error_coding.h src/main.cpp src/maps/map.cpp src/util/ds/string_graph.c  src/menu.c src/util/strings/strings_c.c src/util/file/config_handler.c src/util/file/config_handler.h src/global.h src/error_coding.h src/error_coding.c)

set(TEST_FOLDER tests)
include_directories(${TEST_FOLDER}/include)
add_executable(DeUberTest ${TEST_FOLDER}/maps/map_test.cpp src/maps/map.cpp)

