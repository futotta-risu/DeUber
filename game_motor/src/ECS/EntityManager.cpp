//
// Created by erikberter on 18/03/2020.
//

#include "ECS/EntityManager.h"

#include "ECS/components/sprite_component.h"


EntityManager::EntityManager(){
    loading_order.push_back(1);
    loading_order.push_back(2);
}

void EntityManager::draw(){
    for(std::size_t order_t : loading_order)
        for(auto& t : man.get_group(order_t))
            t->draw();
}

void EntityManager::update(){
    man.refresh();
    man.update();
}

void EntityManager::set_place(int x, int y){
    for(std::size_t order_t : loading_order)
        for(auto& t : man.get_group(order_t))
            t->get_component<Sprite_component>().set_place(x,y);
}