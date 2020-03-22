//
// Created by erikberter on 18/03/2020.
//

#ifndef DEUBER_ANIMATION_H
#define DEUBER_ANIMATION_H

class Animation{
private:

public:

    int index, frames, speed;

    Animation() = default;

    Animation(int index_t, int frames_t, int speed_t){
        index = index_t;
        frames = frames_t;
        speed = speed_t;
    }


};

#endif //DEUBER_ANIMATION_H
