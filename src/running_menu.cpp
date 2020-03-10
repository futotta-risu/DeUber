//
// Created by erikberter on 10/03/2020.
//

#include "running_menu.h"

#include <iostream>
#include <windows.h>
// TODO add also option to sleep in UNIX

#ifdef _WIN32
#define clrscr() system("cls");
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif


void print_logo(){
    printf("\n\toooooooooo.             ooooo     ooo  .o8\n");
    printf("\t`888'   `Y8b            `888'     `8' \"888                          \n");
    printf("\t888      888  .ooooo.   888       8   888oooo.   .ooooo.  oooo d8b\n");
    printf("\t888      888 d88' `88b  888       8   d88' `88b d88' `88b `888\"\"8P \n");
    printf("\t888      888 888ooo888  888       8   888   888 888ooo888  888\n");
    printf("\t888     d88' 888    .o  `88.    .8'   888   888 888    .o  888\n");
    printf("\to888bood8P'   `Y8bod8P'    `YbodP'     `Y8bod8P' `Y8bod8P' d888b    \n");
    printf("\n \n");
}


void running_menu_launch(map *mapa, generic_algorithm *algorithm){
    running_menu_data act_dat;
    std::cout << "Se va a proceder a ejecutar el programa. Antes de ello, si lo desea, puede optar por cambiar "
                 "parte de la configuración de la misma." << std::endl;
    std::cout << "\t1) Config" << std::endl;
    std::cout << "\t2) Run" << std::endl;

    int opcion;
    std::cin >> opcion;

    if(opcion == 1) act_dat = config_running_menu_type();
    else run_program(mapa, algorithm);


}

void run_program(map *mapa, generic_algorithm *algorithm){
    std::cout << "\n STEP1 \n";
    mapa->print_map();
    for(int i = 2; i < 100; i++){
        std::cout << "\n STEP" << i <<  " \n";
        algorithm->move_cars(mapa);
        mapa->print_map();
        Sleep(1000);
        clrscr();
        print_logo();
    }
}
running_menu_data config_running_menu_type(){

    running_menu_data data_t;
    int option;
    do{
        std::cout << "Bienvenido al menu de configuración, establezca que desea modificar:" << std::endl;
        std::cout << "\t1) Animacion" << std::endl;
        std::cout << "\t1) Guardar y salir" << std::endl;
        std::cin >> option;
        while(option<0 || option>2){
            std::cout << "Opcion incorrecta. Escribala de nuevo." << std::endl;
            std::cin >> option;
        }

        if(option==0) data_t.is_animated = !data_t.is_animated;
        else break;
    }while(option!=2);
    return data_t;
}