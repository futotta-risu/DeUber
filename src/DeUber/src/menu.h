//
// Created by erikberter on 2/18/2020.
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

void map_menu();
void algorithm_menu();
void config_menu();
void home_menu();

const static struct {
    const char *name;
    void (*func)(void);
} function_map [] = {
        {"home_menu", home_menu },
        { "map_menu", map_menu },
        { "algorithm_menu", algorithm_menu },
        { "config_menu", config_menu }
};

int call_function(const char *name);

void load_menu_graph(const char *file_name);
void run_menu(const char *file_name);



#if defined (__cplusplus)
}
#endif

#endif //DEUBER_MENU_H
