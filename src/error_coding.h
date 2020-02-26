//
// Created by erikberter on 2/26/2020.
//

#ifndef DEUBER_ERROR_CODING_H
#define DEUBER_ERROR_CODING_H

#if defined (__cplusplus)
extern "C" {
#endif

typedef enum  _error_codes {
    E_SUCCESS                   = 0,
    E_MENU_FILE_NOT_FOUND       = -1,
    E_INVALID_NODE_NUMBER       = -2,
    E_INVALID_EDGE_NUMBER       = -3,
    E_BUFFER_OVERFLOW_ERROR     = -4,
    E_INVALID_NODE_CONNECTION   = -5,
    E_STRING_SIZE_ERROR         = -6,
    E_INVALID_MENU_GRAPH_FILE   = -7
} error_c;


typedef struct  _error_info{
    error_c code_type;
    const char *error_name;
    const char *error_description;
} _error_info;

extern struct _error_info _error_val[];
extern const int _error_n;
struct _error_info get_error_by_type(error_c err_c);

void print_error(error_c err_c);

#if defined (__cplusplus)
}
#endif
#endif //DEUBER_ERROR_CODING_H
