//
// Created by erikberter on 2/26/2020.
//

#include <error_coding.h>
#include <stdio.h>
struct _error_info _error_val[] = {
        {E_SUCCESS,             "Success",             "Success"},
        {E_MENU_FILE_NOT_FOUND, "File Not Found",      "The file could not be retrieved"},
        {E_INVALID_NODE_NUMBER, "Invalid Node Number", "An invalid number of nodes was given"},
        {E_INVALID_EDGE_NUMBER, "Invalid Edge Number", "An invalid number of edge number was given"},
        {E_BUFFER_OVERFLOW_ERROR, "Buffer Overflow Error", "Error trying to allocate memory"},
        {E_INVALID_NODE_CONNECTION, "Invalid Edge Connection", " An invalid node was given to an edge creation"},
        {E_STRING_SIZE_ERROR, "String Size Error","String exceeded maximum size"},
        {E_INVALID_MENU_GRAPH_FILE,"Invalid Menu Graph File", "The format in the Menu Graph file is invalid"},
        {E_TOO_LONG_NUMBER_GRAPH_FILE, "Too Long Number", "A number in the graph file is too long."},
        {E_UNREACHABLE_MAP_DIR, "Unreachable Map Dir", "The map directory can't be reached"},
        };
const int _error_n = sizeof(_error_val) / sizeof(struct _error_info);

// Could be improved y implementing some kind of hash function bashed on the code number to the array position
// if the array gets long enough.
struct _error_info get_error_by_type(error_c err_c) {
    for (int i = 0; i < _error_n; i++)
        if (_error_val[i].code_type == err_c)
            return _error_val[i];
    return _error_val[1];
}

void print_error(error_c err_c){
    struct _error_info err_inf= get_error_by_type(err_c);
    printf("Ha habido un error %i (%s) : %s \n", err_inf.code_type, err_inf.error_name, err_inf.error_description);
}