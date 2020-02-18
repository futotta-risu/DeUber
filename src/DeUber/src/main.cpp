#include <iostream>
#include "menu.h"
int main() {

    // TODO Config file
    char* menu_file = "../data/menu.dg";
    load_menu_graph(menu_file);
    return 0;
}
