//
// Created by whiwho on 11/02/2020.
//

#ifndef DEUBER_CAR_H
#define DEUBER_CAR_H

enum operation{
    NONE = 0, WORKING = 1
};

class car {
private:
    int coord_x, coord_y;
    int point_t;
    operation op;
public:
    car(){
        coord_x = 0;
        coord_y = 0;
        op = NONE;
        point_t = 0;
    }
    car(int coord_x, int coord_y) : coord_x{coord_x}, coord_y{coord_y}{
        op = NONE;
        point_t = 0;
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

    void set_operation(operation i_op){
        op = i_op;
    }

    operation get_operation(){
        return op;
    }

    int set_points(int i_point_t){
        point_t = i_point_t;
    }
    int add_points(int i_point){
        point_t+= i_point;
    }
    int get_points(){
        return point_t;
    }


};


#endif //DEUBER_CAR_H
