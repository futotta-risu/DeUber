//
// Created by whiwho on 18/03/2020.
//

#include "EntityManager.h"

Manager EntityManager::man;

EntityManager::EntityManager(){
    loading_order.push_back(G_TILES);
    loading_order.push_back(G_CAR);
}

void EntityManager::update(){
    EntityManager::man.refresh();
    EntityManager::man.update();

}