//
// Created by erikberter on 22/03/2020.
//

#ifndef DEUBER_GAME_COMPONENT_H
#define DEUBER_GAME_COMPONENT_H

#include <SDL.h>
#include "ECS/EntityManager.h"
#include "ECS/asset_manager.h"
#include "../../window_manager/include/component/component_list.h"


class Collision_component;

class GameApp : public WindowComponent{
private:
    int counter = 0;
public:
    EntityManager ent_man;
    Asset_manager ast_man;
    std::vector<Collision_component*> colliders;

    GameApp() : WindowComponent(){
        set_container();
    };


    void input() override {
    };
    void update() override {
        ent_man.update();
        counter++;
    };
    void draw(SDL_Renderer *ren) override {
        ent_man.draw();
    };
    void update_layout() override {
        ent_man.set_place(get_dst()->x, get_dst()->y);
    };

    Entity& add_entity(){
        return ent_man.man.add_entity();
    };



};

#endif //DEUBER_GAME_COMPONENT_H
