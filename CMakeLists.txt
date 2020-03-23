cmake_minimum_required(VERSION 3.10)
project(DeUber)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include/SDL2")

IF (WIN32)
    set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/libSDL2.dll.a;${CMAKE_CURRENT_LIST_DIR}/lib/libSDL2_image.dll.a;${CMAKE_CURRENT_LIST_DIR}/lib/libSDL2main.a;${CMAKE_CURRENT_LIST_DIR}/lib/libSDL2_test.a;${CMAKE_CURRENT_LIST_DIR}/lib/libSDL2_ttf.dll.a")
    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
ELSE()
    set(SDL2_LIBRARIES "SDL2;SDL2_ttf;SDL_image")
    set($ENV[XDG_RUNTIME_DIR] "~/codigo/temp")
ENDIF()


add_subdirectory(window_manager)
add_subdirectory(game_motor)

include_directories(${SDL2_INCLUDE_DIRS} )

add_executable(DeUber src/main.cpp src/maps/map.cpp src/util/ds/string_graph.c  src/menu.c src/util/strings/strings_c.c src/util/file/config_handler.c src/error_coding.c  src/running_menu.cpp src/run_handler.cpp src/maps/car.cpp src/visual/visual_run_handler.cpp )


target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC window_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC game_motor)
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})


set(TEST_PROJECT_NAME DeUber_test)
set(TEST_FOLDER tests)
include_directories(${TEST_FOLDER}/include)
add_executable(${TEST_PROJECT_NAME} ${TEST_FOLDER}/maps/map_test.cpp src/maps/map.cpp src/maps/car.cpp src/util/strings/strings_c.c)
target_include_directories( ${TEST_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

