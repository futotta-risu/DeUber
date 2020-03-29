//
// Created by whiwho on 17/03/2020.
//

#include "ECS/entity_manager.h"
#include "ECS/Components/sprite_component.h"
#include "ECS/Components/collision_component.h"


EntityManager::EntityManager(){
    loading_order.push_back(G_PLAYER);
    loading_order.push_back(G_ENEMY);
    loading_order.push_back(G_TILES);
}

void EntityManager::draw(){
    for(std::size_t order_t : loading_order)
        for(auto& t : EntityManager::man.get_group(order_t))
            t->draw();

}

void EntityManager::update(){
    man.refresh();
    man.update();
    /*
    for(auto& enem : man.get_group(G_ENEMY))
        if(Collision::is_collision(enem->get_component<Collision_component>().coll,get_player().get_component<Collision_component>().coll ))
            std::cout << " Han chocdo!!" << std::endl;*/
}



void EntityManager::set_place(int x, int y){
    for(std::size_t order_t : loading_order)
        for(auto& t : man.get_group(order_t))
            t->get_component<SpriteComponent>().set_place(x,y);
}