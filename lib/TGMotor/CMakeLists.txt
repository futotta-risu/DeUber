cmake_minimum_required(VERSION 3.10)
project(TGMotor CXX)

set(CMAKE_CXX_STANDARD 14)


file(GLOB_RECURSE GAME_MOTOR_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*)
add_library(${PROJECT_NAME} ${GAME_MOTOR_SOURCES})

add_library(sub::TGMotor ALIAS ${PROJECT_NAME})

add_dependencies(${PROJECT_NAME} SDL2 JSON PLOG)
target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} SDL2 JSON PLOG)
