//
// Created by 34634 on 2/17/2020.
//

#include "string_graph.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

adj_list_node* create_adj_list_node(int vertex, char text[]){
    assert(strlen(text)<MAX_NODE_STR_LENGTH);
    adj_list_node *temp_node = (adj_list_node *)malloc(sizeof(adj_list_node));

    assert(temp_node!=NULL);
    temp_node->vertex = vertex;
    temp_node->next = NULL;
    strcpy(temp_node->text, text);
    return temp_node;
}

void add_node(string_graph* g, int pos, char text[]){
    assert(strlen(text)<MAX_NODE_STR_LENGTH);
    node *temp_node = (node *)malloc(sizeof(node));
    assert(temp_node!=NULL);
    strcpy(temp_node->text, text);
    temp_node->neightbors=0;
    g->node_list[pos] = *temp_node;
}

string_graph* create_graph(int v){
    string_graph* graph = (string_graph *)malloc(sizeof(string_graph));
    assert(graph != NULL);


    graph->total_nodes = v;
    graph->total_edges = 0;
    graph->adj_list_arr = malloc(v * sizeof(adj_list));
    graph->node_list = malloc(v * sizeof(node));

    if(graph->adj_list_arr == NULL){
        free(graph);
        return NULL;
    }
    for(int i = 0; i < v; i++){
        graph->adj_list_arr[i].head = NULL;
        graph->adj_list_arr[i].total_members = 0;
    }
    return graph;
}
void add_edge(string_graph* g, int src, int dest, char text[]){
    assert(src <= g->total_nodes && src > 0);
    assert(dest <= g->total_nodes && dest > 0);

    // TODO Is alredy the edge in?

    adj_list_node *temp_node = create_adj_list_node(dest, text);
    assert(temp_node != NULL);

    temp_node->next = g->adj_list_arr[src].head;
    g->adj_list_arr[src].head = temp_node;
    g->adj_list_arr[src].total_members++;

}
