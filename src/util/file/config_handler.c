//
// Created by erikberter on 25/02/2020.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "util/strings/strings_c.h"
#include "util/file/config_handler.h"

config_property* config_vals;
int n_config;

void save_config(){
    FILE *fp = fopen(config_name, "w");
    printf("config: %s", config_name);
    for(int i_temp = 0; i_temp < n_config; i_temp++)
        fprintf(fp, "%s : %s\n", (config_vals + i_temp)->property_name,(config_vals + i_temp)->property_value );

    fclose(fp);

}

void change_property(char* property_name, char* property_value){
    for(unsigned int i = 0; i < n_config; i++){
        if(strcmp((config_vals +i)->property_name, property_name) == 0)
            (config_vals +i)->property_value =  strdup(property_value);
    }
    save_config();
}



void read_config(const char* file_name){
    // If it is alredy in memory, free it and re-read it
    if(n_config>0){
        n_config = 0;
        free(config_vals);
    }
    config_name = strdup(file_name);
    FILE *fptr = fopen(config_name, "r");

    assert(fptr  != NULL);

    size_t line_s;
    char * buffer = NULL;
    char delim[] = ":";

    size_t file_lines = 0;

    while ((line_s = getline(&buffer, &line_s, fptr)) != -1) {
        buffer = trim(buffer);
        line_s = strlen(buffer);
        // TODO Bug 1 : Empty lines bug
        // Comment on the file
        if(buffer[0] == '#' || line_s==0)
            continue;
        file_lines++;
    }

    config_vals = (config_property*)malloc(file_lines * sizeof(config_property));

    fptr = fopen(config_name, "r");
    assert(fptr  != NULL);

    for(int temp_val = 0; (line_s = getline(&buffer, &line_s, fptr)) != -1; temp_val++) {
        buffer = trim(buffer);
        line_s = strlen(buffer);
        // TODO Bug 1 : Empty lines bug
        // Comment on the file
        if(buffer[0] == '#' || line_s==0){
            temp_val--;
            continue;
        }

        char *property_name  = strdup(trim(strtok(buffer, delim)));
        char *property_value = strdup(trim(strtok(NULL, delim)));
        config_property cp_temp = {property_name, property_value};
        config_vals[temp_val] = cp_temp;
        n_config++;

    }
    fclose(fptr);
}

void print_config(){
    for(int temp_val = 0; temp_val < n_config; temp_val++)
        printf("\tValor %i) %s : %s\n", temp_val,
               config_vals[temp_val].property_name, config_vals[temp_val].property_value);
}

char* get_config_val(const char* key){
    for(unsigned int i = 0; i < n_config; i++)
        if(strcmp((config_vals +i)->property_name, key) == 0)
            return (config_vals +i)->property_value;
    return NULL;
}