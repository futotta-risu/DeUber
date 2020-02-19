//
// Created by erikberter on 17/02/2020.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "util/strings/strings_c.h"
#include "menu.h"

int call_function(const char *name){
    for (int i = 0; i < (sizeof(function_map) / sizeof(function_map[0])); i++) {
        if (!strcmp(function_map[i].name, name) && function_map[i].func) {
            function_map[i].func();
            return 0;
        }
    }
    return -1;
}

void load_menu_graph(const char* file_name){
    FILE *fptr = fopen(file_name, "r");
    assert(fptr  != NULL);

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
                assert(strcmp(node_expected,"Node")==0);

                node_number_t = atoi(trim(strtok(NULL, delim)));
                assert(node_number_i < MAX_GRAPH_SIZE && node_number_i>=0);

                node_number_i = node_number_t;
                menu_tree = create_graph(node_number_t);
                assert(menu_tree!= NULL);

                phase++;
                continue;
            }
            case 1:{
                // check if end of nodes

                int node_act = atoi(trim(strtok(buffer, delim)));
                assert(node_act < node_number_t && node_act>=0);

                char *node_text = trim(strtok(NULL, delim));
                add_node(menu_tree, node_act, node_text);
                if(--node_number_i==0){
                    phase++;
                    continue;
                }
                continue;
            }
            case 2:{
                char *edge_expected = trim(strtok(buffer, delim));

                assert(strcmp(edge_expected,"Edge")==0);

                edge_number_t = atoi(trim(strtok(NULL, delim)));
                edge_number_i = edge_number_t;

                assert(edge_number_t <= node_number_t*(node_number_t-1) && edge_number_t>=0);

                menu_tree->total_edges = edge_number_t;
                phase++;
                continue;
            }
            case 3:{

                int edge_src = atoi(trim(strtok(buffer, delim)));
                int edge_dst = atoi(trim(strtok(NULL, delim)));

                assert(edge_src < node_number_t && edge_src>=0);
                assert(edge_dst < node_number_t && edge_dst>=0);

                char *node_text = trim(strtok(NULL, delim));
                add_edge(menu_tree, edge_src, edge_dst, node_text);

                if(--edge_number_i==0){
                    phase++;
                    continue;
                }
                continue;
            }
            default:
                return;
        }

    }
    printf("Load Compelted \n\n");

    fclose(fptr);
}
void run_menu(const char* file_name){
    load_menu_graph(file_name);
    int act_node = 0;
    int temp_input_line;
    size_t temp_list_size = 0;

    // TODO Redefine this loop
    for(unsigned int i = 0; i < 200; i++){
        // TODO Delete when its working
        //printf("Estamos en el nodo %i.\n", act_node);
        //printf("Paso %i : %s\n",i, get_node_var(menu_tree,act_node));
        call_function(get_node_var(menu_tree,act_node));

        // TODO check input type validity
        unsigned short invalid_input = 0;
        do{
            invalid_input = 0;
            print_next_node_list(menu_tree, act_node, &temp_list_size);
            printf("Introduzca la opcion que desea:");
            scanf("%i",&temp_input_line);
            fflush(stdin);
            printf("\n");
            if(temp_input_line<0 || temp_input_line>= temp_list_size){
                printf("Por favor, introduzca un numero de entre las opciones.\n");
                invalid_input = 1;
            }
        }while(invalid_input==1);
        act_node = get_next_node(menu_tree, act_node, temp_input_line);
    }
}

void home_menu(){
    printf("Estamos en el Home Menu\n");
}
void map_menu(){
    printf("Estamos en el Menu de Mapas.\n");
}
void algorithm_menu(){
    printf("Estamos en el Menu de Algoritmos.\n");
}
void config_menu(){
    printf("Estamos en el Menu de Configuracion.\n");
}

