//
// Created by whiwho on 15/03/2020.
//

#ifndef TEMPGAMEMOTOR_VECTOR2D_H
#define TEMPGAMEMOTOR_VECTOR2D_H

#include <iostream>

template <class T>
class Vector2D{
public:
    T x,y;

    Vector2D(){
        x = 0.0f;
        y = 0.0f;
    }
    Vector2D(T x_t, T y_t){
        x = x_t;
        y=y_t;
    }

    template<class Q>
    friend Vector2D<Q>& operator +(Vector2D<Q>&  v1, Vector2D<Q>&  v2 ){
        v1.x += v2.x;
        v1.y += v2.y;
        return v1;
    }
    template<class Q>
    friend Vector2D<Q>& operator -(Vector2D<Q>&  v1, Vector2D<Q>&  v2 ){
        v1.x -= v2.x;
        v1.y -= v2.y;
        return v1;
    }
    template<class Q>
    friend Vector2D<Q>& operator *(Vector2D<Q>&  v1, Vector2D<Q>&  v2 ){
        v1.x *= v2.x;
        v1.y *= v2.y;
        return v1;
    }
    template<class Q>
    friend Vector2D<Q>& operator /(Vector2D<Q>&  v1, Vector2D<Q>&  v2 ){
        v1.x /= v2.x;
        v1.y /= v2.y;
        return v1;
    }

    Vector2D<T>& operator +=(const Vector2D<T>& vec){
        this->x = this->x+vec.x;
        this->y = this->y+vec.y;
        return *this;
    }
    Vector2D<T>& operator -=(const Vector2D<T>& vec){
        this->x = this->x-vec.x;
        this->y = this->y-vec.y;
        return *this;
    }
    Vector2D<T>& operator *=(const Vector2D<T>& vec){
        this->x = this->x*vec.x;
        this->y = this->y*vec.y;
        return *this;
    }
    template<typename Q>
    Vector2D<T>& operator *=(const Q& val){
        this->x = this->x*val;
        this->y = this->y*val;
        return *this;
    }
    Vector2D<T>& operator /=(const Vector2D<T>& vec){
        this->x = this->x/vec.x;
        this->y = this->y/vec.y;
        return *this;
    }

    template<class Q>
    friend std::ostream& operator <<(std::ostream& stream, const Vector2D<Q>& vec){
        stream << "Vector2D(" << vec.x << "-" << vec.y << ")";
        return stream;
    }

    Vector2D<T>& operator*(const int& val){
        this->x *= val;
        this->y *= val;
        return *this;
    }

    void Zero(){
        this->x = 0;
        this->y = 0;
    }

};

#endif //TEMPGAMEMOTOR_VECTOR2D_H
