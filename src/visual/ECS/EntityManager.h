//
// Created by whiwho on 18/03/2020.
//

#ifndef DEUBER_ENTITYMANAGER_H
#define DEUBER_ENTITYMANAGER_H

#include "ECS.h"

enum group_labels : std::size_t {
    G_CAR, G_TILES
};

class EntityManager {
private:
    std::vector<std::size_t> loading_order;
public:
    static Manager man;

    EntityManager();

    void draw(){
        for(std::size_t order_t : loading_order)
            for(auto& t : EntityManager::man.get_group(order_t))
                t->draw();
    }
    void update();

    std::vector<Entity*>& get_entities(std::size_t identifier){return man.get_group(identifier);};

};


#endif //DEUBER_ENTITYMANAGER_H
