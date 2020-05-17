#ifndef WINDOW_MANAGER_CTEXTBOX_H
#define WINDOW_MANAGER_CTEXTBOX_H

#include <CComponent.h>
#include <SDL_ttf.h>
#include <CFont.h>
#include <locale>
#include <cstring>
#include <utils/collision.h>
#include <CMouse.h>


class CTextBox : public CComponent{
private:

    bool focused = false;
    CFont font;

    int key_board_tick = 0;
    int last_char = -1;
    int last_char_tick = 0;

    // Component Values
    std::string text_value;

    // Component Renders
    SDL_Texture *tex =  nullptr;
    SDL_Rect pos = {0,0};
public:
    CTextBox() = default;
    ~CTextBox() = default;

    std::vector<std::pair<int,int> > keyboard_printable_chars = {
            {4,40},{42,43},{44,49},{54,57}};

    // Runtime Handlers
    void input() override {
        if(CMouse::isClickLeft())
            set_focused(is_inside_rect(get_dst(), CMouse::mouse_x, CMouse::mouse_y));

        if(focused){
            if(key_board_tick>0){
                key_board_tick--;
                return;
            }
            const Uint8 *keys = SDL_GetKeyboardState(nullptr);
            auto key_code = static_cast<SDL_Scancode>(0);
            for(auto p : keyboard_printable_chars)
                for(int i = p.first; i < p.second; i++)
                    if(keys[i]) key_code = static_cast<SDL_Scancode>(i);

            if(key_code>0 && key_code!=42) text_value += static_cast<char>(SDL_GetKeyFromScancode(key_code));
            else if(key_code==42 && !text_value.empty()) text_value.pop_back();


            if(key_code>0){
                set_drawn(false);
                key_board_tick = 5;
            }
        }

    };
    void update() override {};
    void draw(SDL_Renderer* ren) override {
        if(!is_drawn()){
            TTF_Font* font_r = TTF_OpenFont(font.get_font().c_str(), std::max(get_size().h-15,20));
            int w,h;
            SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font_r, text_value.c_str(), font.get_color());
            TTF_SizeText(font_r, text_value.c_str(), &w, &h);
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

    void set_focused(bool focused_t){
        if(focused_t == focused) return;
        set_background(SDL_Color_dsp(get_background_color(),
                                     (focused_t) ? -30 : 30));
        focused = !focused;
    }

    std::string get_text(){return text_value;};
    void set_text(const std::string& text_value_t){text_value = text_value_t;};

    void update_layout() override{};
};
#endif //WINDOW_MANAGER_CTEXTBOX_H
