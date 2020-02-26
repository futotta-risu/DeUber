//
// Created by erikberter on 2/17/2020.
//

#include "string_graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

adj_list_node* create_adj_list_node(int vertex, char text[]){
    adj_list_node *temp_node = (adj_list_node *)malloc(sizeof(adj_list_node));
    if(temp_node == NULL) return NULL;

    temp_node->vertex = vertex;
    temp_node->next = NULL;
    strcpy(temp_node->text, text);
    return temp_node;
}

/**
 * Adjunta el texto al nodo el nodo del grafo seleccionado.
 *
 * @param g string_graph
 * @param pos Posicion de nodo
 * @param text Texto a adjuntar
 * @return Error Code
 */
error_c add_node_text(string_graph** g, int pos, char text[]){
    if(strlen(text) > MAX_NODE_STR_LENGTH) return E_STRING_SIZE_ERROR;
    node *temp_node = (node *)malloc(sizeof(node));
    if(temp_node == NULL) return E_BUFFER_OVERFLOW_ERROR;

    strcpy(temp_node->text, text);
    temp_node->neightbors=0;
    (*g)->node_list[pos] = *temp_node;
    return E_SUCCESS;
}

error_c create_graph(int v, string_graph** s_graph){
    (*s_graph)= (string_graph *)malloc(sizeof(string_graph));
    if(*s_graph == NULL) return E_BUFFER_OVERFLOW_ERROR;

    (*s_graph)->total_nodes = v;
    (*s_graph)->total_edges = 0;
    (*s_graph)->adj_list_arr = malloc(v * sizeof(adj_list));
    (*s_graph)->node_list = malloc(v * sizeof(node));

    if((*s_graph)->adj_list_arr == NULL){
        free(s_graph);
        return E_BUFFER_OVERFLOW_ERROR;
    }
    for(int i = 0; i < v; i++){
        (*s_graph)->adj_list_arr[i].head = NULL;
        (*s_graph)->adj_list_arr[i].total_members = 0;
    }


    return E_SUCCESS;
}
error_c add_edge(string_graph** g, int src, int dest, char text[]){
    if(src > (*g)->total_nodes ||  src <0) return E_INVALID_NODE_CONNECTION;
    if(dest > (*g)->total_nodes ||  dest <0) return E_INVALID_NODE_CONNECTION;
    if(strlen(text) >= MAX_NODE_STR_LENGTH) return E_STRING_SIZE_ERROR;
    // TODO Is alredy the edge in?

    adj_list_node *temp_node = create_adj_list_node(dest, text);
    if(temp_node == NULL) return E_BUFFER_OVERFLOW_ERROR;

    temp_node->next = (*g)->adj_list_arr[src].head;
    (*g)->adj_list_arr[src].head = temp_node;
    (*g)->adj_list_arr[src].total_members++;

}

/**
 * Devuelve el texto adjuntado al nodo en cuestion.
 *
 * @param g string_graph
 * @param n Numero del nodo(ordenado desde 0 al n-1)
 * @return Texto del nodo
 */
char* get_node_text(string_graph* g,int n){
    return g->node_list[n].text;
}

void print_next_node_list(string_graph* g, int src, size_t* list_size){
    assert(src<g->total_nodes);
    adj_list_node* temp_node = g->adj_list_arr[src].head;

    *list_size = 0;
    while(temp_node!= NULL){
        printf("\t%i) %s\n", (*list_size)++,  temp_node->text);
        temp_node = temp_node->next;
    }

}

/**
 * Obtiene el indice del nodo con el que conecta la n-ava arista de src.
 *
 * @param g Grafo de texto
 * @param src Nodo de salida
 * @param n Arista Buscada
 * @return (|src| < n)-1 ; (|src|>= n) src.edges[n]
 */
int get_next_node(string_graph* g, int src, int n){
    adj_list_node* temp_node = g->adj_list_arr[src].head;
    while(n--){
        temp_node = temp_node->next;
        if(temp_node == NULL)
            return -1;
    }
    return temp_node->vertex;
}
