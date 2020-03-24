cmake_minimum_required(VERSION 3.10)
project(SDL2)

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include/SDL2")

IF (WIN32)
    set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2.dll.a;${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2_image.dll.a;${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2main.a;${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2_test.a;${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2_ttf.dll.a")
    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
ELSE()
    set(SDL2_LIBRARIES "SDL2;SDL2_ttf;SDL_image")
    set($ENV[XDG_RUNTIME_DIR] "~/codigo/temp")
ENDIF()

add_library(SDL2 INTERFACE)
target_include_directories(SDL2 INTERFACE ${SDL2_INCLUDE_DIRS} )
target_link_libraries(SDL2 INTERFACE ${SDL2_LIBRARIES} )
