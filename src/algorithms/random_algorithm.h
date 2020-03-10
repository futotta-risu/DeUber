//
// Created by whiwho on 07/03/2020.
//

#ifndef DEUBER_RANDOM_ALGORITHM_H
#define DEUBER_RANDOM_ALGORITHM_H

#include "generic_algorithm.h"

#include <stdlib.h>
class random_algorithm : public generic_algorithm {
public:
    int get_best_move(map *map_t, car car_t){
      return rand() % 4+1;
    };

    void move_cars(map *map_t){
        for(int i = 0; i < map_t->get_car_list_size(); i++){
            car car_t = map_t->get_car(i);
            int dir = get_best_move(map_t, car_t);
            map_t->move_car(car_t.get_id(),dir);
        }
    }
private:
};


#endif //DEUBER_RANDOM_ALGORITHM_H
