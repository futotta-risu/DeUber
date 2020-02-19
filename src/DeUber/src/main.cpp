
#include "menu.h"
#include "util/strings/strings_c.h"
#include<stdio.h>
#include<string.h>
#include "maps/map.h"

int main() {
    // TODO Config file
    constexpr const char* menu_file = "../data/menu.dg";
    constexpr const char* map_file = "../data/maps/ej1.map";
    //run_menu(menu_file);
    map mapa;
    mapa.read_map(map_file);
    mapa.print_map();

    return 0;
}
