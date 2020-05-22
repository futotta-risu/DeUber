#ifndef WINDOWMANAGER_CBUTTON_H
#define WINDOWMANAGER_CBUTTON_H

#include "CAbstractButton.h"

#include "SDL_ttf.h"
#include "CLabel.h"

#include <iostream>
#include <algorithm>
#include <utility>
#include <misc/CFont.h>

class CButton : public CAbstractButton{
private:
    std::string button_text;
    CFont font;
    CText::alignment txt_alg = {CText::alignment_h::CENTER, CText::alignment_v::CENTER};

    SDL_Rect pos = {0,0};
    SDL_Texture *tex =  nullptr;
public:

    CButton() : CAbstractButton(), button_text{""}{set_default();};
    explicit CButton(std::string  button_text_t) : CAbstractButton(),
            button_text{std::move(button_text_t)}{set_default();};

    ~CButton() = default;

    CFont* get_font(){
        return &font;
    }

    void set_default(){
        set_background(244,244,244,255);
        set_size({100,40});
    }
    void draw(SDL_Renderer *ren) override{
        if(!is_drawn()){
            // TODO Refactor. Similar code in CLabel and every text in component
            int w,h;
            if(get_background_color().a==0)
                set_background(get_parent()->get_background_color());
            TTF_Font* font_r = TTF_OpenFont(font.get_font().c_str(), font.get_size());
            SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font_r, button_text.c_str(), font.get_color());
            TTF_SizeText(font_r, button_text.c_str(), &w, &h);
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
    }
    std::string get_text(){return button_text;};
    void set_text(const std::string& button_text_t){button_text = button_text_t;set_drawn(false);}

    void set_alignment(CText::alignment txt_alg_t){txt_alg = txt_alg_t;}
    void set_alignment(CText::alignment_h txt_alg_t){txt_alg.horizontal = txt_alg_t;}
    void set_alignment(CText::alignment_v txt_alg_t){txt_alg.vertical = txt_alg_t;}
};

#endif //WINDOWMANAGER_CBUTTON_H
