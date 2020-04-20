cmake_minimum_required(VERSION 3.10)
project(JSON)

add_library(JSON INTERFACE)
target_include_directories(JSON INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include/)