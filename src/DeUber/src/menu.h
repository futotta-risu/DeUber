//
// Created by 34634 on 2/18/2020.
//

#ifndef DEUBER_MENU_H
#define DEUBER_MENU_H
#if defined (__cplusplus)
extern "C" {
#endif

#include "util/ds/string_graph.h"

const int MAX_BUFFER_SIZE = 1024;
const int MAX_GRAPH_SIZE = 128;

string_graph *menu_tree;

void load_menu_graph(char *file_name);

void run_menu(char *file_name);

void map_menu();

void algorithm_menu();

void config_menu();

void home_menu();

#if defined (__cplusplus)
}
#endif

#endif //DEUBER_MENU_H
