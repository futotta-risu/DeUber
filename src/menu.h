//
// Created by erikberter on 2/18/2020.
//

#ifndef DEUBER_MENU_H
#define DEUBER_MENU_H

#if defined (__cplusplus)
extern "C" {
#endif

#include "util/ds/string_graph.h"
#include "error_coding.h"

#include "algorithms/algorithm_type.h"
const int MAX_BUFFER_SIZE = 1024;
const int MAX_GRAPH_SIZE = 128;

struct running_info{
    char* map_name;
    enum algorithm_type alg_name;
};

string_graph *menu_tree;

void map_menu( struct running_info* run_info);
void algorithm_menu( struct running_info* run_info);
void config_menu( struct running_info* run_info);
void home_menu( struct running_info* run_info);
void config_change(struct running_info* run_info);
void config_print(struct running_info* run_info);


const static struct {
    const char *name;
    void (*func)( struct running_info* run_info);
} function_map [] = {
        {"home_menu", home_menu },
        { "map_menu", map_menu },
        { "algorithm_menu", algorithm_menu },
        { "config_menu", config_menu },
        {"config_change", config_change},
        {"config_print", config_print}
};

int call_function(const char *name,  struct running_info* run_info);

error_c load_menu_graph(const char *file_name);
struct running_info run_menu(const char *file_name);



#if defined (__cplusplus)
}
#endif

#endif //DEUBER_MENU_H
