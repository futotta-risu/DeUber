//
// Created by whiwho on 18/03/2020.
//

#ifndef DEUBER_MAP_ERRORS_H
#define DEUBER_MAP_ERRORS_H

#include <stdio.h>
#include "map.h"

class invalid_coords : public std::exception{
private:
    const char* msg = "Invalid coordinates error";
public:

    invalid_coords(){
        msg = "Invalid coordinates error";
    }
    invalid_coords(int x, int y){
        char* const msg_t = "";
        sprintf(msg_t, "Invalid coordinates error. You tried: (%d,%d)", x,y);
        msg = static_cast<const char*>(msg_t);
    }
    invalid_coords(int x, int y, Map* map_t){
        char* const msg_t = "";
        sprintf(msg_t, "Invalid coordinates error. You tried: (x:%d,y:%d) but the bounds where (x:%d,y:%d)",
                x,y, (*map_t).get_width(),map_t->get_height());
        msg = static_cast<const char*>(msg_t);
    }

    const char *what() const throw(){
        return msg;
    }
};

class map_out_of_bounds : public std::exception{
private:
    const char* msg = "Map out of bounds. Consider changing the MAX_MAP_WIDTH or the MAP_MAX_HEIGHT";
public:

    map_out_of_bounds(){
        msg = "Map out of bounds. Consider changing the MAX_MAP_WIDTH or the MAP_MAX_HEIGHT";
    }
    map_out_of_bounds(int x, int y){
        if(x < 0 || y < 0) msg = "You tried to reshape to negative values";
        else {
            char* const msg_t = "";
            sprintf(msg_t,
                    "Map out of bounds. Consider changing the MAX_MAP_WIDTH or the MAP_MAX_HEIGHT. You tried: (%d,%d)",
                    x, y);
            msg = static_cast<const char *>(msg_t);
        }
    }
    const char *what() const throw(){
        return msg;
    }
};


#endif //DEUBER_MAP_ERRORS_H
