//
// Created by erikberter on 2/17/2020.
//

#ifndef DEUBER_STRING_GRAPH_H
#define DEUBER_STRING_GRAPH_H

#if defined (__cplusplus)
extern "C" {
#endif

#define MAX_NODE_STR_LENGTH 128

#include <string.h>
#include <error_coding.h>

typedef struct adj_list_node adj_list_node;
typedef struct adj_list adj_list;
typedef struct node node;

struct node {
    char text[MAX_NODE_STR_LENGTH];
    int neightbors;
};

struct adj_list_node {
    int vertex;
    char text[MAX_NODE_STR_LENGTH];
    struct adj_list_node *next;
};

struct adj_list {
    int total_members;
    struct adj_list_node *head;
};

typedef struct {
    int total_nodes;
    int total_edges;
    adj_list *adj_list_arr;
    node *node_list;
} string_graph;

adj_list_node* create_adj_list_node(int vertex, char text[]);

error_c create_graph(int v, string_graph **s_graph);
error_c add_edge(string_graph **g, int src, int dest, char text[]);
error_c add_node_text(string_graph **g, int pos, char text[]);

char* get_node_text(string_graph *g, int n);
int get_next_node(string_graph *g, int src, int n);
void print_next_node_list(string_graph *g, int src, size_t *list_size);

#if defined (__cplusplus)
}
#endif
#endif //DEUBER_STRING_GRAPH_H
