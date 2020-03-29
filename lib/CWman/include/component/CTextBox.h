//
// Created by whiwho on 25/03/2020.
//

#ifndef WINDOW_MANAGER_CTEXTBOX_H
#define WINDOW_MANAGER_CTEXTBOX_H

#include <CComponent.h>
#include <SDL_ttf.h>
#include <CFont.h>
#include <locale>
#include <cstring>
#include <utils/collision.h>

const char* key_map = "abcdefghijklmnopqrstuvwxyz";

class CTextBox : public CComponent{
private:

    // Component Metadata
    bool focused;
    CFont font;

    int key_board_tick = 0;
    int last_char = -1;
    int last_char_tick = 0;

    // Component Values
    std::string text_value;

    // Component Renders
    SDL_Texture *tex;
    SDL_Rect pos;
public:
    CTextBox() = default;
    ~CTextBox() = default;

    std::vector<std::pair<int,int> > keyboard_printable_chars = {
            {4,40},{42,43},{44,49},{54,57}};

    // Runtime Handlers
    void input() override {
        int x, y;
        // Check if inside
        if(SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
            set_focused(is_inside_rect(get_dst(), x, y));

        if(focused){
            if(key_board_tick>0){
                key_board_tick--;
                return;
            }
            const Uint8 *keys = SDL_GetKeyboardState(NULL);
            SDL_Scancode key_code = static_cast<SDL_Scancode>(0);
            for(auto p : keyboard_printable_chars)
                for(int i = p.first; i < p.second; i++)
                    if(keys[i]) key_code = static_cast<SDL_Scancode>(i);

            if(key_code>0 && key_code!=42) text_value += static_cast<char>(SDL_GetKeyFromScancode(key_code));
            else if(key_code==42 && !text_value.empty()) text_value.pop_back();


            if(key_code>0){
                set_drawed(false);
                key_board_tick = 5;
            }
        }

    };
    void update() override {};
    void draw(SDL_Renderer* ren) override {
        if(!is_drawed()){
            TTF_Font* font_r = TTF_OpenFont(font.get_font().c_str(), std::max(get_size().h-15,20));
            int w,h;
            SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font_r, text_value.c_str(), font.get_color());
            TTF_SizeText(font_r, text_value.c_str(), &w, &h);
            tex = SDL_CreateTextureFromSurface(ren, surfaceMessage);
            SDL_FreeSurface(surfaceMessage);
            TTF_CloseFont(font_r);

            pos.w = std::min(w, get_size().w);
            pos.h = std::min(h, get_size().h);

            set_drawed(true);
        }
        draw_CUI(ren);
        pos.x = get_pos().x;
        pos.y = get_pos().y;
        SDL_RenderCopy(ren,tex,NULL,&pos);
    };

    void set_focused(bool focused_t){
        if(focused_t == focused) return;
        set_background(SDL_Color_dsp(get_background_color(),
                                     (focused_t) ? -30 : 30));
        focused = !focused;
    }

    std::string get_text(){return text_value;};
    void set_text(std::string text_value_t){text_value = text_value_t;};

    void update_layout() override{};
};
#endif //WINDOW_MANAGER_CTEXTBOX_H
