#include <meta/CTextProperties.h>
#include <iostream>

int CText::get_pos_by_aligm_h(CText::alignment_h alignment_t, int parent_w, int child_w){
    switch(alignment_t){
        case CText::alignment_h::LEFT:
            break;
        case CText::alignment_h::CENTER:
            if(child_w < parent_w)
                return (parent_w - child_w)/2;
            break;
        case CText::alignment_h::RIGHT:
            if(child_w < parent_w)
                return parent_w - child_w;
            break;
    }
    return 0;
}
int CText::get_pos_by_aligm_v(CText::alignment_v alignment_t, int parent_h, int child_h){
    switch(alignment_t){
        case CText::alignment_v::TOP:
            break;
        case CText::alignment_v::CENTER:
            if(child_h < parent_h)
                return (parent_h - child_h)/2;
            break;
        case CText::alignment_v::BOTTOM:
            if(child_h < parent_h)
                return parent_h - child_h;
            break;
    }
    return 0;
}