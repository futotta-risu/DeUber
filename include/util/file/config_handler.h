//
// Created by erikberter on 25/02/2020.
//

#ifndef DEUBER_CONFIG_HANDLER_H
#define DEUBER_CONFIG_HANDLER_H


#if defined (__cplusplus)
extern "C" {
#endif

#include <string.h>
char* config_name;


typedef struct{
    char* property_name;
    char* property_value;
} config_property;

extern config_property* config_vals;


extern int n_config;

void change_property(char* property_name, char* property_value);

void read_config(const char* file_name);
void save_config();

void print_config();

#if defined (__cplusplus)
}
#endif

#endif //DEUBER_CONFIG_HANDLER_H
