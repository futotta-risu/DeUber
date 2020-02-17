//
// Created by whiwho on 17/02/2020.
//

#include "util/ds/string_graph.h"
#include <stdio.h>
#include <assert.h>
#include "util/strings/strings_c.h"

const int MAX_BUFFER_SIZE = 1024;
const int MAX_GRAPH_SIZE = 128;

string_graph* menu_tree;

void load_menu_graph(){
    FILE *fptr;
    assert(fptr = fopen("program.txt", "r") != NULL);

    ssize_t line_s;
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
    while ((line_s = getline(&buffer, &line_s, fptr)) != -1) {
        buffer = trim(buffer);
        line_s = strlen(buffer);

        // Comment on the file
        if(line_s[0] == '#')
            continue;

        switch(phase){
            case 0:{
                char *node_expected = trim(strtok(buffer, delim));
                assert(strcmp(node_expected,"Node"));

                char *node_number_c = trim(strtok(buffer, delim));
                node_number_i = node_number_c -'0';
                assert(node_number_i < MAX_GRAPH_SIZE && node_number_i>=0);

                menu_tree = create_graph(node_number_i);
                assert(menu_tree!= NULL);

                phase++;
                continue;
            }
            case 1:{
                char *node_expected = trim(strtok(buffer, delim));
                // check if end of nodes
                if(strcmp(node_expected,"end")){
                    phase++;
                    continue;
                }
                int node_number_i = node_expected -'0';
                assert(node_number_i < node_number_i && node_number_i>=0);

                char *node_text = trim(strtok(buffer, delim));
                add_node(menu_tree, node_number_i, node_text);
                continue;
            }
            case 2:{
                char *edge_expected = trim(strtok(buffer, delim));
                assert(strcmp(edge_expected,"Edge"));

                char *edge_number_c = trim(strtok(buffer, delim));
                edge_number_i = edge_number_c -'0';
                assert(edge_number_i < node_number_i*(node_number_i-1)/2 && edge_number_i>=0);

                menu_tree->total_edges = edge_number_i;
                phase++;
                continue;
            }
            case 3:{
                // TODO Acabar esto
                char *edge_expected = trim(strtok(buffer, delim));
                // check if end of nodes
                if(strcmp(edge_expected,"end")){
                    phase++;
                    continue;
                }
                int node_number_i = node_expected -'0';
                assert(node_number_i < node_number_i && node_number_i>=0);

                char *node_text = strtok(buffer, delim);
                node_text = trim(node_text);
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
void run_menu(){
    load_menu_graph();

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
