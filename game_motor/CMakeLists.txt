cmake_minimum_required(VERSION 3.10)
project(game_motor CXX)

set(CMAKE_CXX_STANDARD 14)

get_filename_component(PARENT_DIR ../ ABSOLUTE)

set(SDL2_INCLUDE_DIRS "../include/SDL2")
IF (WIN32)
    set(SDL2_LIBRARIES "${PARENT_DIR}/lib/libSDL2.dll.a;${PARENT_DIR}/lib/libSDL2_image.dll.a;${PARENT_DIR}/lib/libSDL2main.a;${PARENT_DIR}/lib/libSDL2_test.a;${PARENT_DIR}/lib/libSDL2_ttf.dll.a")
    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
ELSE()
    set(SDL2_LIBRARIES "SDL2;SDL2_ttf;SDL_image")
    set($ENV[XDG_RUNTIME_DIR] "~/codigo/temp")
ENDIF()


add_library(${PROJECT_NAME} src/texture_manager.cpp src/ECS/asset_manager.cpp src/ECS/ECS.cpp src/ECS/EntityManager.cpp src/game_component.cpp)

include_directories(${SDL2_INCLUDE_DIRS} )

add_library(sub::game_motor ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS} )
target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})
