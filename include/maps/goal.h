//
// Created by whiwho on 19/03/2020.
//

#ifndef DEUBER_GOAL_H
#define DEUBER_GOAL_H


class Goal{
private:
public:
    int active = true;
    Goal() = default;
    ~Goal() = default;

    void destroy(){active = false;};
};
#endif //DEUBER_GOAL_H
