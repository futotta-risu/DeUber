//
// Created by whiwho on 23/03/2020.
//

#ifndef DEUBER_COMPONENT_LABEL_H
#define DEUBER_COMPONENT_LABEL_H

#include "CComponent.h"

#include "SDL_ttf.h"
#include "SDL.h"
#include <functional>
#include <iostream>

#include "utils/colors.h"

class CLabel : public CComponent {
private:

    // Component Metadata
    CFont font;
    // Component Values
    std::string lbl_tex;

    // Component Render
public:
    CLabel() : CComponent(),lbl_tex{""}{set_default();};
    CLabel(std::string lbl_text_t) : CComponent(), lbl_tex{std::move(lbl_text_t)}{set_default();};
    ~CLabel() = default;

    void set_default(){
        set_background(int_to_SDL_Color(255,255,255,255));
        set_size({100,40});
        font.set_color(int_to_SDL_Color(0,0,0,255));
        set_border_size(0);
    }

    // Runtime Handlers
    void input() override {};
    void update() override {};
    void draw(SDL_Renderer* ren) override {
        if(!is_drawn()){
            if(get_background_color().a)
                set_background(get_parent()->get_background_color());
            TTF_Font* font_r = TTF_OpenFont(font.get_font().c_str(), 128);

            SDL_Surface* surfaceMessage = TTF_RenderText_Shaded(font_r, lbl_tex.c_str(), font.get_color(),get_background_color());
            set_tex_CUI(SDL_CreateTextureFromSurface(ren, surfaceMessage));
            SDL_FreeSurface(surfaceMessage);
            TTF_CloseFont(font_r);
            //SDL_QueryTexture(Message, NULL, NULL, &(get_dst()->w), &(get_dst()->h));
            set_drawn(true);
        }
        draw_CUI(ren);
    };
    virtual void update_layout(){};
    void set_text(const std::string& text){
        set_drawn(false);
        lbl_tex = text;
    }
};

#endif //DEUBER_COMPONENT_LABEL_H
