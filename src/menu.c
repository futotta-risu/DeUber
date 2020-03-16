//
// Created by erikberter on 17/02/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "util/strings/strings_c.h"
#include "menu.h"
#include "util/file/config_handler.h"
#include "global.h"

#ifdef _WIN32
#define clrscr() system("cls");
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

int call_function(const char *name, struct running_info* run_info){
    for (int i = 0; i < (sizeof(function_map) / sizeof(function_map[0])); i++) {
        if (!strcmp(function_map[i].name, name) && function_map[i].func) {
            function_map[i].func(run_info);
            return 0;
        }
    }
    return -1;
}

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

string_graph *menu_tree;


error_c load_menu_graph(const char* file_name){
    FILE *fptr = fopen(file_name, "r");
    if(fptr == NULL) return E_BUFFER_OVERFLOW_ERROR;

    size_t line_s;
    char * buffer = NULL;
    char delim[] = ":";

    /**
     * Phase 1 - Get Node Count
     * Phase 2 - Get Node Names
     * Phase 3 - Get Edge Count
     * Phase 4 - Get Edge Vals
     */
    unsigned short phase = 0;
    int node_number_i = 0;
    int edge_number_i = 0;
    int node_number_t = 0;
    int edge_number_t = 0;
    while ((line_s = getline(&buffer, &line_s, fptr)) != -1) {
        buffer = trim(buffer);
        line_s = strlen(buffer);
        //printf("##La linea tiene tamanio %i y valor \"%s\".\n", line_s, buffer);
        // TODO Bug 1 : Empty lines bug
        // Comment on the file
        if(buffer[0] == '#' || line_s==0)
            continue;

        switch(phase){
            case 0:{
                char *node_expected = trim(strtok(buffer, delim));

                if(strcmp(node_expected,"Node")!=0) return E_INVALID_MENU_GRAPH_FILE;

                node_number_i = node_number_t = atoi(trim(strtok(NULL, delim)));
                if(node_number_i >= MAX_GRAPH_SIZE || node_number_i<0)
                    return E_INVALID_MENU_GRAPH_FILE;

                error_c err_c = create_graph(node_number_t, &menu_tree);
                if(err_c) return err_c;

                phase++;
                continue;
            }
            case 1:{
                int node_act = atoi(trim(strtok(buffer, delim)));
                if(node_act > node_number_t || node_act < 0)
                    return E_INVALID_NODE_NUMBER;

                char *node_text = trim(strtok(NULL, delim));
                error_c err_c = add_node_text(&menu_tree, node_act, node_text);
                if(err_c != 0) return err_c;

                if(--node_number_i==0) phase++;

                continue;
            }
            case 2:{
                char *edge_expected = trim(strtok(buffer, delim));
                if(strcmp(edge_expected,"Edge")!=0) return E_INVALID_MENU_GRAPH_FILE;

                edge_number_i = edge_number_t = atoi(trim(strtok(NULL, delim)));
                if(edge_number_t > node_number_t*(node_number_t-1) || edge_number_t<0)
                    return E_INVALID_EDGE_NUMBER;

                menu_tree->total_edges = edge_number_t;
                phase++;
                continue;
            }
            case 3:{
                int edge_src = atoi(trim(strtok(buffer, delim)));
                int edge_dst = atoi(trim(strtok(NULL, delim)));

                if(edge_dst > node_number_t || edge_dst < 0) return E_INVALID_NODE_CONNECTION;
                if(edge_src > node_number_t || edge_src < 0) return E_INVALID_NODE_CONNECTION;

                char *node_text = trim(strtok(NULL, delim));
                add_edge(&menu_tree, edge_src, edge_dst, node_text);

                if(--edge_number_i==0)  phase++;
                continue;
            }
        }
    }
    printf("Load Completed \n\n");
    fclose(fptr);

    return E_SUCCESS;
}
struct running_info run_menu(const char* file_name){
    error_c er_t;
    struct running_info r_info = {"", BFS};
    er_t = load_menu_graph(file_name);

    // TODO Make the running info to have error handling to work with the errors
    if(er_t != E_SUCCESS){
        print_error(er_t);
        return  r_info;
    }


    int act_node = 0;
    int temp_input_line;
    size_t temp_list_size = 0;

    // TODO Redefine this loop
    for(unsigned int i = 0; i < 200; i++){
        // TODO Delete when its working
        //printf("Estamos en el nodo %i.\n", act_node);
        //printf("Paso %i : %s\n",i, get_node_var(menu_tree,act_node));
        clrscr();
        print_logo();
        call_function(get_node_text(menu_tree,act_node),&r_info);
        // TODO check input type validity
        unsigned short invalid_input = 0;
        do{
            invalid_input = 0;
            print_next_node_list(menu_tree, act_node, &temp_list_size);
            printf("Introduzca la opcion que desea:");
            scanf("%i",&temp_input_line);
            fflush(stdin);
            printf("\n");
            if(temp_input_line == -1) return r_info;
            if(temp_input_line<0 || temp_input_line>= temp_list_size){
                printf("Por favor, introduzca un numero de entre las opciones.\n");
                invalid_input = 1;
            }
        }while(invalid_input==1);

        act_node = get_next_node(menu_tree, act_node, temp_input_line);
    }
    return r_info;
}


void home_menu( struct running_info* run_info){
    printf("Estamos en el Home Menu\n");
    printf("Estado del pack informativo \n");
    printf("\n\tRecuerda que para ejecutar el programa debes escribir -1.\n");
    printf("\n Map Name : %s \n Algorithm %i\n\n", run_info->map_name, run_info->alg_name);
}
void map_menu( struct running_info* run_info){

    DIR *d;
    struct dirent *dir;
    d = opendir("../data/maps");
    if (d){
        printf("Escoja el mapa que quiera usar de ahora en adelante.\n");
        for(int i = 0 ;(dir = readdir(d)) != NULL; i++){
            if(dir->d_name[0]=='.')
                continue;
            printf("\t\t%i)%s\n",i, dir->d_name);
        }
        closedir(d);
    }else{
        // TODO Error
        return;
    }
    printf("Escriba algo:");
    int i_v;
    scanf("%i", &i_v);
    fflush(stdin);
    d = opendir("../data/maps");
    for (int i = 0; (dir = readdir(d)) != NULL; i++){
        if(dir->d_name[0]=='.')
            continue;
        if(i_v == i){
            run_info->map_name = strdup(dir->d_name);
            break;
        }
    }
    closedir(d);
}
void algorithm_menu( struct running_info* run_info){
    printf("Estamos en el Menu de Algoritmos.\n");
}
void config_menu( struct running_info* run_info){
}

void config_change(struct running_info* run_info){
    read_config(config_file);
    char input_val[64];
    do{
        printf("\n Si desea hacer algun cambio escriba \"cambio\", si desea salir escriba \"salir\".\n");

        scanf("%s",input_val);

        printf("\n Si desea hacer algun cambio escriba \"cambio\", si desea salir escriba \"salir\".\n");
        if(strcmp(input_val,"salir")==0) break;
        if(strcmp(input_val,"cambio")==0){
            char input_property_name[64];
            char input_property_value[64];
            printf("Introduzca el nombre de la propiedad.\n");
            scanf("%s", input_property_name);

            printf("Introduzca el valor de la propiedad.\n");
            scanf("%s", input_property_value);


            change_property(strdup(input_property_name), strdup(input_property_value));
        }
        printf("Ninguna eleccion \n");
    }while(1==1);


}
void config_print(struct running_info* run_info){
    read_config(config_file);
    print_config();
    printf("Pulse una tecla para continuar....");
    int i = 0;
    scanf("%i", &i);
}
