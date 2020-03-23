//
// Created by erikberter on 18/03/2020.
//

#ifndef DEUBER_ENTITYMANAGER_H
#define DEUBER_ENTITYMANAGER_H

#include <SDL_render.h>
#include "ECS.h"


class EntityManager {
private:
    std::vector<std::size_t> loading_order;
public:
    Manager man;

    EntityManager();

    void draw();
    void update();

    void set_place(int x, int y);

    std::vector<Entity*>& get_entities(std::size_t identifier){return man.get_group(identifier);};

};


#endif //DEUBER_ENTITYMANAGER_H
