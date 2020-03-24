//
// Created by whiwho on 23/03/2020.
//

#ifndef DEUBER_COMPONENT_LABEL_H
#define DEUBER_COMPONENT_LABEL_H

#include "window_component.h"

#include "SDL_ttf.h"
#include "SDL.h"
#include <functional>
#include <iostream>

class ComponentLabel : public WindowComponent {
private:

    // Component Metadata

    // Component Values
    std::string lbl_val;

    // Component Render
    SDL_Texture* tex;
public:
    ComponentLabel() : lbl_val{""}{};
    ComponentLabel(std::string lbl_text);
    ~ComponentLabel();

    // Runtime Handlers
    void input() override {};
    void update() override {};
    void draw(SDL_Renderer* ren) override {};
};

#endif //DEUBER_COMPONENT_LABEL_H
