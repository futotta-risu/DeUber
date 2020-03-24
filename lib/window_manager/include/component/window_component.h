//
// Created by erikberter on 20/03/2020.
//

#ifndef WINDOWMANAGER_WINDOW_COMPONENT_H
#define WINDOWMANAGER_WINDOW_COMPONENT_H

#include <string>
#include <SDL_render.h>

const unsigned int DEFAULT_WIDTH     =   100u;
const unsigned int DEFAULT_HEIGHT    =   100u;

class WindowComponent{
private:
    int pos_x, pos_y, width, height;
    SDL_Rect dst;

    bool container = false;
    bool drawed = false;

    std::string component_id;
public:

    static int id;

    bool visible;

    WindowComponent();
    WindowComponent(int pos_x, int pos_y) : pos_x{pos_x}, pos_y{pos_y},
    component_id{"Component_"+std::to_string(id++)}{set_dst();visible=true;};

    virtual void input() = 0;
    virtual void update() = 0;
    virtual void draw(SDL_Renderer *ren) = 0;

    void set_dst(){
        dst.x = pos_x;
        dst.y = pos_y;
        dst.h = 40;
        dst.w = 100;
    }
    SDL_Rect* get_dst(){
        return &dst;
    }

    void set_bounds(int pos_x_t, int pos_y_t, int width_t, int height_t){
        pos_x = pos_x_t;
        pos_y = pos_y_t;
        width = width_t;
        height = height_t;
        dst.x = pos_x;
        dst.y = pos_y;
        dst.h = height;
        dst.w = width;
    }

    void set_id(std::string component_id_t){
        component_id = component_id_t;
    }

    std::string get_id(){
        return component_id;
    }

    void set_container(){
        container = true;
    }
    bool is_container(){
        return container;
    }

    void set_drawed(){
        drawed = true;
    }

    bool is_drawed(){
        return drawed;
    }

    virtual void update_layout() = 0;
};

#endif //WINDOWMANAGER_WINDOW_COMPONENT_H
