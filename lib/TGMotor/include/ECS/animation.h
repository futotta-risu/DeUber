//
// Created by whiwho on 16/03/2020.
//

#ifndef TEMPGAMEMOTOR_ANIMATION_H
#define TEMPGAMEMOTOR_ANIMATION_H

class Animation{
private:

public:

    int index, frames, speed;

    Animation() : index{1}, frames{1}, speed{10}{};

    Animation(int index_t, int frames_t, int speed_t){
        index = index_t;
        frames = frames_t;
        speed = speed_t;
    }


};

#endif //TEMPGAMEMOTOR_ANIMATION_H
