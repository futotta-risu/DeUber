//
// Created by whiwho on 11/02/2020.
//

#ifndef DEUBER_CAR_H
#define DEUBER_CAR_H

#include <queue>
#include "../global.h"

enum operation{
    NONE = 0, WORKING = 1
};

class car {

private:
    int id;
    int coord_x, coord_y;
    int point_t;
    operation op;

    std::queue<int> moves;
public:

    int dir;

    static int car_id;
    static std::vector<car> read_car_list_file(const char* file_path);

    car(){
        dir = 0;
        coord_x = 0;
        coord_y = 0;
        op = NONE;
        point_t = 0;
        id = car_id++;
    }
    car(int coord_x, int coord_y) : coord_x{coord_x}, coord_y{coord_y}{
        op = NONE;
        point_t = 0;
        id = car_id++;
    };
    car(int coord_x, int coord_y, int id_t) : coord_x{coord_x}, coord_y{coord_y}{
        op = NONE;
        point_t = 0;
        id = id_t;
    };
    ~car() = default;

    void set_coords(int i_coord_x, int i_coord_y){
        // TODO check validity
        coord_x = i_coord_x;
        coord_y = i_coord_y;
    }

    int get_coord_x(){
        return coord_x;
    }

    int get_coord_y(){
        return coord_y;
    }

    int get_id(){
        return id;
    }

    void set_operation(operation i_op){
        op = i_op;
    }

    operation get_operation(){
        return op;
    }

    int get_move(){
        int move_t = moves.front();
        moves.pop();
        if(moves.empty())
            op = NONE;

        return move_t;
    }
    void add_move(int dir){
        moves.push(dir);
        op=WORKING;
    }

    int set_points(int i_point_t){
        point_t = i_point_t;
        return point_t;
    }
    int add_points(int i_point){
        point_t+= i_point;
        return point_t;
    }
    int get_points(){
        return point_t;
    }


};




#endif //DEUBER_CAR_H
