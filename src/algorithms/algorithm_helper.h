//
// Created by whiwho on 10/03/2020.
//

#ifndef DEUBER_ALGORITHM_HELPER_H
#define DEUBER_ALGORITHM_HELPER_H

#include "generic_algorithm.h"
#include "random_algorithm.h"


generic_algorithm* get_algorithm_by_type(algorithm_type alg_type){
    switch(alg_type){
        case RANDOM:
            random_algorithm *ran_alg = new random_algorithm;
            return ran_alg;
    }
    return nullptr;
}



#endif //DEUBER_ALGORITHM_HELPER_H
