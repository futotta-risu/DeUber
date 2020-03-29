//
// Created by erikberter on 22/03/2020.
//

#ifndef DEUBER_GAME_COMPONENT_H
#define DEUBER_GAME_COMPONENT_H

#include <SDL.h>
#include <game.h>
#include "ECS/entity_manager.h"
#include "ECS/asset_manager.h"

#include "CComponent.h"

class Collision_component;

class GameApp : public CComponent{
private:
    int counter = 0;
public:
    Game* g;

    GameApp(SDL_Renderer** ren, const char* map_file_name) : CComponent(){
        set_container();
        g = new Game();
        g->load_defs(ren, map_file_name);

    };


    void input() override {
    };
    void update() override {
        g->e_man.update();
        counter++;
    };
    void draw(SDL_Renderer *ren) override {
        g->e_man.draw();
    };
    void update_layout() override {
        g->e_man.set_place(get_dst()->x, get_dst()->y);
    };

    Entity& add_entity(){
        return g->e_man.man.add_entity();
    };



};

#endif //DEUBER_GAME_COMPONENT_H
