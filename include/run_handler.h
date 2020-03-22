//
// Created by erikberter on 16/03/2020.
//

#ifndef DEUBER_RUN_HANDLER_H
#define DEUBER_RUN_HANDLER_H

#include "menu.h"

class run_handler {
private:
    bool visual;

    struct running_info run_inf;
public:


    run_handler(bool visual_t);
    ~run_handler() = default;


    void non_visual_handler();
    void visual_handler();
};


#endif //DEUBER_RUN_HANDLER_H
