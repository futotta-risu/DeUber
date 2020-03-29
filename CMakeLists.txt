cmake_minimum_required(VERSION 3.10)
project(DeUber)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_subdirectory(lib)

file(GLOB_RECURSE DEUBER_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*)
# Hold the following line while the SQL library isn't correctly implemented
list(FILTER DEUBER_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_LIST_DIR}/src/database/*")

add_executable(DeUber ${DEUBER_SOURCES})
target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC CWman TGMotor TGMApp INTERFACE SDL2)


set(TEST_PROJECT_NAME DeUber_test)
set(TEST_FOLDER tests)
add_executable(${TEST_PROJECT_NAME} ${TEST_FOLDER}/maps/map_test.cpp src/maps/map.cpp src/maps/car.cpp src/util/strings/strings_c.c)
target_include_directories( ${TEST_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${TEST_PROJECT_NAME} PUBLIC Catch2)

