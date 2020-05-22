#ifndef WINDOW_MANAGER_CTEXTPROPERTIES_H
#define WINDOW_MANAGER_CTEXTPROPERTIES_H


#include <SDL_rect.h>

namespace CText{

    enum class alignment_h {
        LEFT, CENTER, RIGHT
    };
    enum class alignment_v{
        BOTTOM, CENTER, TOP
    };

    typedef struct{
        alignment_h horizontal;
        alignment_v vertical;
    } alignment;

    int get_pos_by_aligm_h(CText::alignment_h alignment_t, int parent_w, int child_w);
    int get_pos_by_aligm_v(CText::alignment_v alignment_t, int parent_h, int child_h);
}


#endif //WINDOW_MANAGER_CTEXTPROPERTIES_H
