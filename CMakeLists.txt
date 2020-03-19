cmake_minimum_required(VERSION 3.15)
project(DeUber)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include/SDL2")
set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/libSDL2.dll.a;${CMAKE_CURRENT_LIST_DIR}/lib/libSDL2_image.dll.a;${CMAKE_CURRENT_LIST_DIR}/lib/libSDL2main.a;${CMAKE_CURRENT_LIST_DIR}/lib/libSDL2_test.a")

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

include_directories(${SDL2_INCLUDE_DIRS} )

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

include_directories(src/maps src/cars src/util/ds src/util/file src/util/strings src)

add_executable(DeUber src/error_coding.h src/main.cpp src/maps/map.cpp src/util/ds/string_graph.c  src/menu.c src/util/strings/strings_c.c src/util/file/config_handler.c src/util/file/config_handler.h src/global.h src/error_coding.h src/error_coding.c src/algorithms/random_algorithm.h src/algorithms/generic_algorithm.h src/running_menu.cpp src/running_menu.h src/algorithms/algorithm_helper.h src/algorithms/algorithm_type.h src/run_handler.cpp src/run_handler.h src/maps/car.cpp src/algorithms/BFS_algorithm.h src/maps/map_errors.h src/visual/visual_run_handler.cpp src/visual/visual_run_handler.h src/visual/ECS/ECS.cpp src/visual/ECS/ECS.h src/visual/ECS/EntityManager.cpp src/visual/ECS/EntityManager.h src/visual/ECS/objects/car_entity.h src/visual/ECS/objects/tile_entity.h src/visual/ECS/asset_manager.h src/visual/ECS/asset_manager.cpp src/visual/ECS/animation.h src/visual/texture_manager.h src/visual/texture_manager.cpp src/visual/ECS/Components/transform_component.h src/visual/ECS/Components/collision_component.h src/visual/ECS/Components/components.h src/visual/ECS/Components/sprite_component.h src/visual/ECS/Components/tile_component.h src/visual/vector2d.h src/running_info.h src/visual/ECS/objects/goal_entity.h src/visual/ECS/Components/car_component.h src/maps/goal.h src/visual/ECS/Components/goal_component.h)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

set(TEST_FOLDER tests)
include_directories(${TEST_FOLDER}/include)
add_executable(DeUberTest ${TEST_FOLDER}/maps/map_test.cpp src/maps/map.cpp)

