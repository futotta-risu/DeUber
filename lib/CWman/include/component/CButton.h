#ifndef WINDOWMANAGER_CBUTTON_H
#define WINDOWMANAGER_CBUTTON_H

#include "CAbstractButton.h"

#include "SDL_ttf.h"
#include "CLabel.h"

#include <iostream>
#include <algorithm>
#include <utility>
#include <CFont.h>

class CButton : public CAbstractButton{
private:
    std::string button_text;
    CFont font;


    SDL_Rect pos = {0,0};
    SDL_Texture *tex =  nullptr;
public:

    CButton() : CAbstractButton(), button_text{""}{set_default();};
    CButton(std::string  button_text_t) : CAbstractButton(),
            button_text{std::move(button_text_t)}{set_default();};

    ~CButton() = default;

    void set_default(){
        set_background(244,244,244,255);
        set_size({100,40});
    }
    void draw(SDL_Renderer *ren) override{
        if(!is_drawn()){
            // TODO Refactor. Similar code in CLabel and every text in component
            int w,h;
            if(get_background_color().a)
                set_background(get_parent()->get_background_color());
            TTF_Font* font_r = TTF_OpenFont(font.get_font().c_str(), std::max(get_size().h-15,20));
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
        // TODO Generalize this code as a Text::Position. In this case, center.
        if(pos.w < get_size().w)
            pos.x += (get_size().w - pos.w)/2;

        pos.y = get_pos().y;
        SDL_RenderCopy(ren,tex,nullptr,&pos);
    }
    std::string get_text(){return button_text;};
    void set_text(const std::string& button_text_t){button_text = button_text_t;set_drawn(false);}

};

#endif //WINDOWMANAGER_CBUTTON_H
