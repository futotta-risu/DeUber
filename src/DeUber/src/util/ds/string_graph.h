//
// Created by 34634 on 2/17/2020.
//

#ifndef DEUBER_STRING_GRAPH_H
#define DEUBER_STRING_GRAPH_H


#include <vector>
#include <string>

struct string_node{
    std::string value;
    int weigth = 0 ;
    int src, from;
};


struct string_graph{
    bool is_directed = false;
    bool is_weigthed = false;

    std::vector<std::vector<string_node> >  adj_graph;

};

void create_graph(string_graph* g);
void add_node(string_graph* g, std::string val);
void add_edge(string_graph* g, int src, int dest);

void set_weighted(string_graph* g, bool is_weighted){
    g->is_weigthed = is_weighted;
}
bool is_weighted(string_graph* g){
    return g->is_weigthed;
}
void set_directed(string_graph* g, bool is_directed){
    g->is_directed = is_directed;
}
bool is_directed(string_graph* g){
    return g->is_directed;
}
#endif //DEUBER_STRING_GRAPH_H
