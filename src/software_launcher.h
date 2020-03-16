//
// Created by whiwho on 16/03/2020.
//

#ifndef DEUBER_SOFTWARE_LAUNCHER_H
#define DEUBER_SOFTWARE_LAUNCHER_H


#include "menu.h"

class software_launcher {
private:
    struct running_info run_inf;
public:

    software_launcher() = default;

    static bool visual;

    void main_launch();
    void non_visual_handler();
    void visual_handler();
};


#endif //DEUBER_SOFTWARE_LAUNCHER_H
