//
// Created by whiwho on 18/03/2020.
//

#include "ECS.h"

void Entity::add_group(std::size_t group_t){
    group_bitset[group_t] = true;
    manager.add_group(this, group_t);
}