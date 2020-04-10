//
// Created by erikberter on 17/02/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>

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
    for (int i = 0; i < (sizeof(function_map) / sizeof(function_map[0])); i++)
        if (!strcmp(function_map[i].name, name) && function_map[i].func)
            return function_map[i].func(run_info);
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
    int node_number_i = 0, edge_number_i = 0, node_number_t = 0;

    while ((line_s = getline(&buffer, &line_s, fptr)) != -1) {
        buffer = trim(buffer);
        line_s = strlen(buffer);
        // TODO Bug 1 : Empty lines bug
        // Comment on the file
        if(buffer[0] == '#' || line_s==0)
            continue;

        switch(phase){
            case 0:{
                char *node_expected = trim(strtok(buffer, delim));
                if(strcmp(node_expected,"Node")!=0) return E_INVALID_MENU_GRAPH_FILE;

                errno = 0;
                long err_a = strtol(trim(strtok(NULL, delim)), NULL, 10);
                if(err_a == LONG_MAX || err_a == LONG_MIN )
                    return E_TOO_LONG_NUMBER_GRAPH_FILE;
                else if(errno==EINVAL) return E_INVALID_MENU_GRAPH_FILE;
                else node_number_i = node_number_t = (int) err_a;

                if(node_number_i >= MAX_GRAPH_SIZE || node_number_i<0)
                    return E_INVALID_MENU_GRAPH_FILE;

                error_c err_c = create_graph(node_number_t, &menu_tree);
                if(err_c) return err_c;

                phase++;
                continue;
            }
            case 1:{
                int node_act;

                errno = 0;
                long err_a = strtol(trim(strtok(buffer, delim)), NULL, 10);
                if(err_a == LONG_MAX || err_a == LONG_MIN )
                    return E_TOO_LONG_NUMBER_GRAPH_FILE;
                else if(errno==EINVAL) return E_INVALID_MENU_GRAPH_FILE;
                else node_act = (int) err_a;

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

                errno = 0;
                long err_a = strtol(trim(strtok(NULL, delim)), NULL, 10);
                if(err_a == LONG_MAX || err_a == LONG_MIN )
                    return E_TOO_LONG_NUMBER_GRAPH_FILE;
                else if(errno==EINVAL) return E_INVALID_MENU_GRAPH_FILE;
                else edge_number_i = (int) err_a;

                if(edge_number_i > node_number_t*(node_number_t-1) || edge_number_i<0)
                    return E_INVALID_EDGE_NUMBER;

                menu_tree->total_edges = edge_number_i;
                phase++;
                continue;
            }
            case 3:{
                int edge_src, edge_dst;

                errno = 0;
                long err_src = strtol(trim(strtok(buffer, delim)), NULL, 10);
                if(err_src == LONG_MAX || err_src == LONG_MIN  )
                    return E_TOO_LONG_NUMBER_GRAPH_FILE;
                else if(errno==EINVAL) return E_INVALID_MENU_GRAPH_FILE;
                else edge_src = (int) err_src;

                errno = 0;
                long err_dest= strtol(trim(strtok(NULL, delim)), NULL, 10);
                if(err_dest == LONG_MAX || err_dest == LONG_MIN )
                    return E_TOO_LONG_NUMBER_GRAPH_FILE;
                else if(errno==EINVAL) return E_INVALID_MENU_GRAPH_FILE;
                else edge_dst = (int) err_dest;

                if(edge_dst > node_number_t || edge_dst < 0 ||
                        edge_src > node_number_t ||  edge_src < 0) return E_INVALID_NODE_CONNECTION;

                char *node_text = trim(strtok(NULL, delim));
                add_edge(&menu_tree, edge_src, edge_dst, node_text);

                if(--edge_number_i==0)  phase++;
                continue;
            }
            default:
                break;
        }
    }
    printf("Load Completed \n\n");
    fclose(fptr);

    return E_SUCCESS;
}
struct running_info run_menu(const char* file_name){
    read_config("../data/config");
    struct running_info r_info = {"", BFS, E_SUCCESS};
    r_info.err = load_menu_graph(file_name);

    if(r_info.err != E_SUCCESS){
        print_error(r_info.err);
        return r_info;
    }

    int act_node = 0, temp_input_line;
    size_t temp_list_size = 0;

    while(r_info.err == E_SUCCESS){
        clrscr();
        print_logo();
        int res = call_function(get_node_text(menu_tree,act_node),&r_info);
        if( res == -1) return r_info;
        unsigned short invalid_input = 0;
        do{
            if(invalid_input==0)
                print_next_node_list(menu_tree, act_node, &temp_list_size);
            printf("Introduzca la opcion que desea");
            scanf("%i",&temp_input_line);
            fflush(stdin);
            printf("\n");
            if(temp_input_line<0 || temp_input_line>= temp_list_size)
                printf("\nError %i: Por favor, introduzca un numero de entre las opciones.\n",
                       ++invalid_input);
            else invalid_input=0;
        }while(invalid_input>0);

        act_node = get_next_node(menu_tree, act_node, temp_input_line);
    }
    print_error(r_info.err);
    return r_info;
}

int back_menu( struct running_info* run_info){
    return -1;
}

int home_menu( struct running_info* run_info){
    printf("Estamos en el Home Menu\n");
    printf("Estado del pack informativo \n");
    printf("\n Map Name : %s \n Algorithm %i\n\n", run_info->map_name, run_info->alg_name);
    return 0;
}
int map_menu( struct running_info* run_info){

    DIR *d;
    struct dirent *dir;
    d = opendir(get_config_val("map_folder"));
    if (d){
        printf("Escoja el mapa que quiera usar de ahora en adelante.\n");
        for(int i = 0 ;(dir = readdir(d)) != NULL; i++){
            if(dir->d_name[0]=='.')
                continue;
            printf("\t\t%i)%s\n",i, dir->d_name);
        }
        closedir(d);
    }else{
        print_error(E_UNREACHABLE_MAP_DIR);
        return 0;
    }
    printf("Escriba algo:");
    int i_v;
    scanf("%i", &i_v);
    fflush(stdin);
    d = opendir(get_config_val("map_folder"));
    for (int i = 0; (dir = readdir(d)) != NULL; i++){
        if(dir->d_name[0]=='.')
            continue;
        if(i_v == i){
            run_info->map_name = strdup(dir->d_name);
            break;
        }
    }
    closedir(d);
    return 0;
}
int algorithm_menu( struct running_info* run_info){
    int invalid = 1;
    while(invalid!=0){
        printf("Estamos en el Menu de Algoritmos.\n");
        printf("Escoger el Algoritmos:\n\t 1) BFS\n\t 2) Random\n");
        int option;
        scanf("%i", &option);
        switch(option){
            case 1:
                run_info->alg_name = BFS;
                break;
            case 2:
                run_info->alg_name = RANDOM;
                break;
            default:
                invalid = 0;
                printf("Ha introducido un numero invalido.\n\n");
        }
    }
    return 0;
}
int config_menu( struct running_info* run_info){
    return 0;
}

int config_change(struct running_info* run_info){
    // TODO corregir, error fflush
    read_config(config_file);
    char input_val[64];
    do{
        fflush(stdin);
        printf("\n Si desea hacer algun cambio escriba \"cambio\", si desea salir escriba \"salir\".\n");

        scanf("%s",input_val);
        if(strcmp(input_val,"salir")==0) break;
        if(strcmp(input_val,"cambio")==0){
            char input_property_name[64];
            char input_property_value[64];
            printf("Introduzca el nombre de la propiedad.\n");
            scanf("%s", input_property_name);
            printf("Introduzca el valor de la propiedad.\n");
            scanf("%s", input_property_value);

            change_property(strdup(input_property_name), strdup(input_property_value));
        }else printf("Ninguna eleccion \n");
    }while(1);
    return 0;

}
int config_print(struct running_info* run_info){
    read_config(config_file);
    print_config();
    printf("Escriba una tecla para continuar....");
    int i = 0;
    scanf("%i", &i);
    return 0;
}
