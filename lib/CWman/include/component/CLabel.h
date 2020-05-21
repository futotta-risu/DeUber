#ifndef DEUBER_COMPONENT_LABEL_H
#define DEUBER_COMPONENT_LABEL_H

#include <CComponent.h>
#include <CFont.h>


#include "SDL_ttf.h"
#include "SDL.h"
#include <functional>
#include <iostream>

#include "utils/colors.h"

class CLabel : public CComponent {
private:
    CFont font;
    std::string lbl_tex;

    SDL_Rect pos = {0,0};
    SDL_Texture *tex =  nullptr;
public:
    CLabel() : CComponent(),lbl_tex{""}{set_default();};
    explicit CLabel(std::string lbl_text_t) : CComponent(), lbl_tex{std::move(lbl_text_t)}{set_default();};
    ~CLabel() = default;

    CFont* get_font(){
        return &font;
    }

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
            int w,h;
            if(get_background_color().a)
                set_background(get_parent()->get_background_color());
            TTF_Font* font_r = TTF_OpenFont(font.get_font().c_str(), std::max(get_size().h-15,20));
            SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font_r, lbl_tex.c_str(), font.get_color());
            TTF_SizeText(font_r, lbl_tex.c_str(), &w, &h);
            tex = SDL_CreateTextureFromSurface(ren, surfaceMessage);
            SDL_FreeSurface(surfaceMessage);
            TTF_CloseFont(font_r);

            pos.w = std::min(w, get_size().w);
            pos.h = std::min(h, get_size().h);

            set_drawn(true);
        }
        draw_CUI(ren);
        pos.x = get_pos().x;
        pos.y = get_pos().y;
        SDL_RenderCopy(ren,tex,nullptr,&pos);
    };
    virtual void update_layout(){};

    void set_text(const std::string& text){
        set_drawn(false);
        lbl_tex = text;
    }
};

#endif //DEUBER_COMPONENT_LABEL_H
