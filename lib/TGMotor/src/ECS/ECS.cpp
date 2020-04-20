//
// Created by whiwho on 15/03/2020.
//

#include "ECS/ECS.h"

ComponentHelper::map_type ComponentHelper::ComponentMap;
ComponentHelper::map_sct ComponentHelper::ComponentMapSCT;


void Entity::add_group(std::size_t group_t){
    group_bitset[group_t] = true;
    manager.add_group(this, group_t);
}