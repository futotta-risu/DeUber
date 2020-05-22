#ifndef WINDOW_MANAGER_CFONT_H
#define WINDOW_MANAGER_CFONT_H

#include <string>
#include <SDL_pixels.h>

class CFont{
private:
    std::string font_file;
    SDL_Color font_color = {0,0,0,0};
    int size = 20;
public:

    CFont() : font_file{"../res/font/Roboto/Roboto-Regular.ttf"}{};

    std::string get_font(){return font_file;};
    void set_font(std::string& font_file_t){font_file = font_file_t;};

    void set_color(SDL_Color color){ font_color = color;};
    SDL_Color get_color(){return font_color;};

    int get_size(){return size;}
    void set_size(int size_t){if(size_t<=0) return; size = size_t;};

};

#endif //WINDOW_MANAGER_CFONT_H
