//
// Created by erikberter on 10/03/2020.
//

#include "../include/running_menu.h"

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


void running_menu_launch(Map *mapa, generic_algorithm *algorithm){
    running_menu_data act_dat;
    std::cout << "Se va a proceder a ejecutar el programa. Antes de ello, si lo desea, puede optar por cambiar "
                 "parte de la configuración de la misma." << std::endl;


    int option;
    bool is_on_menu = true;
    while(is_on_menu){
        std::cout << "\t1) Config" << std::endl;
        std::cout << "\t2) Run" << std::endl;
        std::cout << "\t3) Salir" << std::endl;
        std::cout << std::endl << " Introduzca el valor que desee: " << std::endl;

        std::cin >> option;
        switch(option){
            case 1:
                act_dat = config_running_menu_type();
                break;
            case 2:
                run_program(mapa, algorithm, act_dat);
                break;
            case 3:
                is_on_menu = false;
            default:
                std::cout << "Ha introducido un valor no valido" << std::endl;
                break;
        }
    }



}

void run_program(Map *mapa, generic_algorithm *algorithm, running_menu_data run_dat){
    std::cout << "\n STEP1 \n";
    mapa->print_map();
    bool is_running = true;
    int timer = 0;
    while(is_running){
        // GAME LOOP
        clrscr();
        print_logo();
        std::cout << "\n STEP" << ++timer <<  std::endl;
        // render
        mapa->print_map();

        // input
        if(!run_dat.is_animated){
            std::cout << std::endl << "Pulsa enter para continuar. Para salir escriba -1" << std::endl;
            int temp;
            std::cin >> temp;
            if(temp == -1) is_running = false;
        }else Sleep(static_cast<int>(1000/run_dat.animated_fps));

        // update
        algorithm->move_cars(mapa);

    }
}
running_menu_data config_running_menu_type(){

    running_menu_data data_t;
    int option;
    do{
        std::cout << "Bienvenido al menu de configuración, establezca que desea modificar:" << std::endl;
        std::cout << "\t1) Animacion : " << data_t.is_animated <<  std::endl;
        std::cout << "\t2) FPS : " << data_t.animated_fps <<  std::endl;
        std::cout << "\t3) Guardar y salir" << std::endl;
        std::cin >> option;
        while(option<0 || option>3){
            std::cout << "Opcion incorrecta. Escribala de nuevo." << std::endl;
            std::cin >> option;
        }

        switch(option){
            case 1:
                data_t.is_animated = !data_t.is_animated;
                break;
            case 2:
                std::cout << "Introduzca los FPS que desee" << std::endl;
                std::cin >> data_t.animated_fps;
                break;
            default:
                break;
        }
    }while(option!=3);
    return data_t;
}