cmake_minimum_required(VERSION 3.10)
project(CWman CXX)

set(CMAKE_CXX_STANDARD 14)


file(GLOB_RECURSE WINDOW_MANAGER_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*)
add_library(${PROJECT_NAME} ${WINDOW_MANAGER_SOURCES} src/CMouse.cpp)

add_library(sub::CWman ALIAS ${PROJECT_NAME})

add_dependencies(${PROJECT_NAME} SDL2)
target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} SDL2)

