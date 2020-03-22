//
// Created by whiwho on 07/03/2020.
//

#ifndef DEUBER_GENERIC_ALGORITHM_H
#define DEUBER_GENERIC_ALGORITHM_H


#include "../maps/map.h"
#include "../maps/car.h"


class generic_algorithm {
public:
    virtual int get_best_move(Map *map_t, car *car_t) = 0;
    virtual void move_cars(Map *map_t) = 0;
private:
};


#endif //DEUBER_GENERIC_ALGORITHM_H
