#ifndef DEUBER_GAME_COMPONENT_H
#define DEUBER_GAME_COMPONENT_H

#include <SDL.h>
#include <game.h>
#include <random>

#include "ECS/entity_manager.h"
#include "ECS/asset_manager.h"

#include "game_man.h"
#include "CComponent.h"


class Collision_component;

class GameApp : public CComponent{
private:
    int counter = 0;
    bool paused = false;

public:
    GameManager *gm;
    Game *g;

    GameApp() : CComponent(){
        set_container();
        gm = new GameManager();
    };

    void load(){
        g = new Game("");

        g->load_defs({});
        gm->set_game(g);
        PLOG_INFO << "Game loaded";
    }

    void input() override {};

    void update() override {
        if(paused) return;
        if(rand()%60==0){gm->add_random_goal();update_layout();}
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

    void set_paused(){
        paused = !paused;
    }
};

#endif //DEUBER_GAME_COMPONENT_H
