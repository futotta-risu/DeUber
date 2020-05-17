//
// Created by erikberter on 20/03/2020.
//

#ifndef WINDOWMANAGER_CBUTTON_H
#define WINDOWMANAGER_CBUTTON_H

#include "CAbstractButton.h"

#include "SDL_ttf.h"

#include <iostream>
#include <algorithm>
#include <CFont.h>

class CButton : public CAbstractButton{
private:
    // Component Metadata
    std::string button_text;
    CFont font;
    // Component vals

    // Component Render

public:

    CButton() : CAbstractButton(), button_text{""}{set_default();};
    CButton(std::string button_text_t) : CAbstractButton(),
            button_text{button_text_t}{set_default();};

    ~CButton() = default;

    void set_default(){
        set_background(244,244,244,255);
        set_size({100,40});
    }
    void draw(SDL_Renderer *ren) override{
        if(!is_drawn()){
            TTF_Font* font_r = TTF_OpenFont(font.get_font().c_str(), 128);

            SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font_r, button_text.c_str(), font.get_color());
            set_tex_CUI(SDL_CreateTextureFromSurface(ren, surfaceMessage));
            SDL_FreeSurface(surfaceMessage);
            TTF_CloseFont(font_r);
            //SDL_QueryTexture(Message, NULL, NULL, &(get_dst()->w), &(get_dst()->h));
            set_drawn(true);
        }
        draw_CUI(ren);
    }
    std::string get_text(){return button_text;};
    void set_text(std::string button_text_t){button_text = button_text_t;set_drawn(false);}

};

#endif //WINDOWMANAGER_CBUTTON_H
