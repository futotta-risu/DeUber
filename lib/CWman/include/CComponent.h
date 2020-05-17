#ifndef WINDOWMANAGER_WINDOW_COMPONENT_H
#define WINDOWMANAGER_WINDOW_COMPONENT_H

#include <string>
#include <SDL_render.h>
#include "CBorder.h"
#include "CUI.h"

#include <algorithm>

const unsigned int DEFAULT_WIDTH     =   100u;
const unsigned int DEFAULT_HEIGHT    =   40u;

class CComponent{
private:
    CUI component_CUI;
    CComponent* parent;

    bool container = false;
    bool drawn= false;
    bool resizable = true;

    std::string component_id;
public:
    static int id;
    bool visible = true;

    CComponent() : component_id{"Component_"+std::to_string(id++)}{};
    ~CComponent() = default;

    virtual void input() = 0;
    virtual void update() = 0;
    virtual void draw(SDL_Renderer *ren) = 0;

    virtual void update_layout() = 0;

    SDL_Rect* get_dst(){return component_CUI.get_dst();}

    void set_id(const std::string& component_id_t){component_id = component_id_t;}
    std::string get_id(){return component_id;}

    void set_container(){container = true;}
    bool is_container(){return container;}

    void set_drawn(bool drawn_t){drawn = drawn_t;}
    bool is_drawn(){return drawn;}

    SDL_Color get_background_color(){return component_CUI.get_background_color();};
    void set_background(SDL_Color bg_color){component_CUI.set_background_color(bg_color);}
    void set_background(int r, int g, int b, int a){
        component_CUI.set_background_color({
            static_cast<Uint8>(r),static_cast<Uint8>(g),static_cast<Uint8>(b),static_cast<Uint8>(a)});};

    void set_border(CBorder& border_t){component_CUI.set_border(border_t);};
    void set_border_color(SDL_Color color_t){component_CUI.set_border_color(color_t);};
    void set_border_size(int size_t){component_CUI.set_border_size(size_t);};

    void set_pos(Position pos){component_CUI.set_pos(pos);};
    Position get_pos(){return *component_CUI.get_coords();};
    void set_size(Dimension d){component_CUI.set_actual_size(d);};
    Dimension get_size(){return component_CUI.get_actual_size();};
    void set_minimum_size(Dimension d){component_CUI.set_minimum_size(d);};

    void set_tex_CUI(SDL_Texture* tex){component_CUI.set_tex(tex);};
    void draw_CUI(SDL_Renderer* ren){component_CUI.draw(ren);};

    void set_parent(CComponent* parent_t){parent = parent_t;};
    CComponent* get_parent(){return parent;};

    void set_resizable(bool resizable_t){resizable = resizable_t;};
    bool is_resizable(){return resizable;};
};

#endif //WINDOWMANAGER_WINDOW_COMPONENT_H
