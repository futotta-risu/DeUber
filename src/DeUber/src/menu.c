//
// Created by whiwho on 17/02/2020.
//


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "util/strings/strings_c.h"
#include "menu.h"


void load_menu_graph(char* file_name){
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
        printf("La linea tiene tamanio %i y valor %s. \n", line_s, buffer);
        // Comment on the file
        if(buffer[0] == '#')
            continue;

        switch(phase){
            case 0:{
                char *node_expected = trim(strtok(buffer, delim));
                assert(strcmp(node_expected,"Node")==0);

                // TODO eliminar esto tras comprobar
                char* temp = trim(strtok(buffer, delim));
                printf("El total de nodos es %s\n", temp);
                node_number_t = atoi(temp);

                printf("El total de nodos es %i\n", node_number_t);
                assert(node_number_i < MAX_GRAPH_SIZE && node_number_i>=0);

                node_number_i = node_number_t;
                menu_tree = create_graph(node_number_t);
                assert(menu_tree!= NULL);

                phase++;
                continue;
            }
            case 1:{
                // check if end of nodes
                node_number_i--;
                if(node_number_i==0){
                    phase++;
                    continue;
                }
                int node_act = atoi(trim(strtok(buffer, delim)));
                printf("El nodo actual es %i - %i\n", node_act, node_number_t);
                assert(node_act < node_number_t && node_act>=0);

                char *node_text = trim(strtok(buffer, delim));
                add_node(menu_tree, node_number_i, node_text);
                continue;
            }
            case 2:{
                char *edge_expected = trim(strtok(buffer, delim));
                assert(strcmp(edge_expected,"Edge"));

                edge_number_t = atoi(trim(strtok(buffer, delim)));
                assert(edge_number_t < node_number_t*(node_number_t-1)/2 && edge_number_t>=0);

                menu_tree->total_edges = edge_number_t;
                phase++;
                continue;
            }
            case 3:{

                // TODO check if the -- is correct
                node_number_i--;
                if(node_number_i==0){
                    phase++;
                    continue;
                }
                int edge_src = atoi(trim(strtok(buffer, delim)));
                int edge_dst = atoi(trim(strtok(buffer, delim)));
                assert(edge_src < node_number_i && edge_src>=0);
                assert(edge_dst < node_number_i && edge_dst>=0);

                char *node_text = trim(strtok(buffer, delim));
                add_node(menu_tree, node_number_i, node_text);
                continue;
            }
            default:{
                return;
            }
        }

    }


    fclose(fptr);
}
void run_menu(char* file_name){
    load_menu_graph( file_name);

}

void map_menu(){
    printf("Escoja el mapa que desee que aparezca:");
}
void algorithm_menu(){
    printf("Escoja el mapa que desee que aparezca:");
}
void config_menu(){
    printf("Escoja el mapa que desee que aparezca:");
}
void home_menu(){
    printf("Escoja el mapa que desee que aparezca:");
}
