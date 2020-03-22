cmake_minimum_required(VERSION 3.15)
project(window_manager CXX)

set(CMAKE_CXX_STANDARD 14)

get_filename_component(PARENT_DIR  ../ ABSOLUTE)

set(SDL2_INCLUDE_DIRS "../include/SDL2")
set(SDL2_LIBRARIES "${PARENT_DIR}/lib/libSDL2.dll.a;${PARENT_DIR}/lib/libSDL2_image.dll.a;${PARENT_DIR}/lib/libSDL2main.a;${PARENT_DIR}/lib/libSDL2_test.a;${PARENT_DIR}/lib/libSDL2_ttf.dll.a")

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

include_directories(${SDL2_INCLUDE_DIRS} )

add_library(${PROJECT_NAME} src/window_handler.cpp src/layout/absolute_layout.cpp  src/component/window_component.cpp  src/layout/vertical_flow_layout.cpp)

add_library(sub::window_manager ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS} )
target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})
