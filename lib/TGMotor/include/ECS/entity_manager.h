//
// Created by whiwho on 17/03/2020.
//

#ifndef TEMPGAMEMOTOR_ENTITY_MANAGER_H
#define TEMPGAMEMOTOR_ENTITY_MANAGER_H


#include "ECS.h"
#include "physics/collision.h"

enum group_labels : std::size_t {
    G_PLAYER=1,G_ENEMY=2, G_COLLIDER=3, G_TILES=4
};

class EntityManager {
private:
     std::vector<std::size_t> loading_order;
public:
    Manager man;

    EntityManager();

    Entity& get_player(){return *man.get_group(G_PLAYER).back();};

    void draw();
    void update();

    std::vector<Entity*>& get_entities(std::size_t identifier){return man.get_group(identifier);};

    void set_place(int x, int y);

    // TODO Change way to add order
    void add_to_order(std::vector<std::size_t> order_t){loading_order = std::move(order_t);}
};


#endif //TEMPGAMEMOTOR_ENTITY_MANAGER_H
