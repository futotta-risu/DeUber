//
// Created by whiwho on 28/03/2020.
//

#ifndef DEUBER_GAMEVISUALIZATOR_H
#define DEUBER_GAMEVISUALIZATOR_H

#include <ECS/ECS.h>

#include <vector>
#include <SDL_render.h>

class GameVisualizator{
private:
public:
    GameVisualizator() = default;
    ~GameVisualizator() = default;

    virtual void init() = 0;
    virtual void draw(std::vector<Entity> draw_c) = 0;

    virtual SDL_Renderer** get_renderer() = 0;
};

#endif //DEUBER_GAMEVISUALIZATOR_H
