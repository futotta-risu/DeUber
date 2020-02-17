//
// Created by 34634 on 2/17/2020.
//

#ifndef DEUBER_STRING_GRAPH_H
#define DEUBER_STRING_GRAPH_H

#include <string.h>

const int MAX_NODE_STR_LENGTH = 32;

typedef struct adj_list_node adj_list_node;
typedef struct adj_list adj_list;
typedef struct node node;

struct node{
    char text[MAX_NODE_STR_LENGTH];
    int neightbors;
};

struct adj_list_node{
    int vertex;
    char text[MAX_NODE_STR_LENGTH];
    struct adj_list_node *next;
};

struct adj_list{
    int total_members;
    struct adj_list_node *head;
};

typedef struct{
    int total_nodes;
    int total_edges;
    adj_list *adj_list_arr;
    node *node_list;
} string_graph;

string_graph* create_graph(int v);
void add_edge(string_graph* g, int src, int dest, char text[]);
void add_node(string_graph* g, int pos, char text[]);

#endif //DEUBER_STRING_GRAPH_H
