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
    Vector2(float scalar) : x(scalar), y(scalar) {}
    Vector2(float x, float y) : x(x), y(y) {}

    float Distance(Vector2 pos) const {
        return std::sqrt((x - pos.x) * (x - pos.x) + (y - pos.y) * (y - pos.y));
    }

    static Vector2 Lerp(Vector2 position, Vector2 destination, float lerpValue) {
        return {
                position.x + (destination.x - position.x) * lerpValue,
                position.y + (destination.y - position.y) * lerpValue
        };
    }

    static Vector2 MiddlePoint(Vector2 first, Vector2 second) {
        return {
                first.x + (second.x - first.x) / 2,
                first.y + (second.y - first.y) / 2
        };
    }

    Vector2 operator+(Vector2 other) const {
        return {x + other.x, y + other.y};
    }

    Vector2 operator-(Vector2 other) const {
        return {x - other.x, y - other.y};
    }

    Vector2 operator/(Vector2 other) const {
        return {x / other.x, y / other.y};
    }

    Vector2 operator/(float other) const {
        return {x / other, y / other};
    }

    Vector2 operator*(float other) const {
        return {x * other, y * other};
    }

    // Negation
    Vector2 operator-() const {
        return {-x, -y};
    }

    bool operator==(Vector2 other) const {
        return (x == other.x && y == other.y);
    }

    bool operator!=(Vector2 other) const {
        return !(*this == other);
    }
};

#endif //KENAZENGINEGAME_VECTOR2_H
