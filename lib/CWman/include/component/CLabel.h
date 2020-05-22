#ifndef DEUBER_COMPONENT_LABEL_H
#define DEUBER_COMPONENT_LABEL_H

#include <CComponent.h>
#include <misc/CFont.h>


#include "SDL_ttf.h"
#include "SDL.h"
#include <functional>
#include <iostream>
#include <meta/CTextProperties.h>

#include "utils/colors.h"

class CLabel : public CComponent {
private:
    CFont font;
    std::string lbl_tex;
    CText::alignment txt_alg = {CText::alignment_h::LEFT, CText::alignment_v::TOP};

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
        set_background(int_to_SDL_Color(255,255,255,0));
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
            if(get_background_color().a==0)
                set_background(get_parent()->get_background_color());
            TTF_Font* font_r = TTF_OpenFont(font.get_font().c_str(), font.get_size());
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
        SDL_Rect pos_t = {pos.x+get_pos_by_aligm_h(txt_alg.horizontal,get_size().w,pos.w),
                          pos.y+get_pos_by_aligm_v(txt_alg.vertical,get_size().h,pos.h),
                          pos.w, pos.h};
        SDL_RenderCopy(ren,tex,nullptr,&pos_t);
    };
    virtual void update_layout(){};

    std::string get_text(){
        return lbl_tex;
    }
    void set_text(const std::string& text){
        set_drawn(false);
        lbl_tex = text;
    }
    void set_alignment(CText::alignment txt_alg_t){txt_alg = txt_alg_t;}
    void set_alignment(CText::alignment_h txt_alg_t){txt_alg.horizontal = txt_alg_t;}
    void set_alignment(CText::alignment_v txt_alg_t){txt_alg.vertical = txt_alg_t;}
};

#endif //DEUBER_COMPONENT_LABEL_H
