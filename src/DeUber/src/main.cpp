
#include "menu.h"
#include "util/strings/strings_c.h"
#include<stdio.h>
#include<string.h>
int main() {
    // TODO Config file
    constexpr const char* menu_file = "../data/menu.dg";
    run_menu(menu_file);


    return 0;
}
