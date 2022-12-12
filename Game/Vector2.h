//
// Created by masterktos on 23.11.22.
//

#ifndef KENAZENGINEGAME_VECTOR2_H
#define KENAZENGINEGAME_VECTOR2_H

#include <cmath>

#include "cmath"

class Vector2 {
public:
    float x, y;
    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}
    float Distance(Vector2 pos) const {
        return std::sqrt((x-pos.x)*(x-pos.x) + (y-pos.y)*(y-pos.y));
    }
    Vector2 operator+(Vector2 other) const {
        return {x+other.x, y+other.y};
    }
    Vector2 operator-(Vector2 other) const {
        return {x-other.x, y-other.y};
    }
    Vector2 operator/(Vector2 other) const {
        return {x/other.x, y/other.y};
    }
    Vector2 operator/(float other) const {
        return {x/other, y/other};
    }
    Vector2 operator*(float other) const {
        return {x*other, y*other};
    }
    // Negation
    Vector2 operator-() const {
        return {-x, -y};
    }
};

#endif //KENAZENGINEGAME_VECTOR2_H
