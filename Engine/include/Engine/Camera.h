//
// Created by MasterKtos on 04.11.2022.
//

#ifndef KENAZENGINEGAME_CAMERA_H
#define KENAZENGINEGAME_CAMERA_H


#include <utility>
#include "Vector2.h"

class SDL_Renderer;

class Camera {
private:
    SDL_Renderer* Renderer;

public:
    Camera(SDL_Renderer* renderer);
    Vector2 Position;
    Vector2 screenDimensions;

    void MoveTo(int x, int y);
    void MoveTo(Vector2 position);
    void Move(int x, int y);
    void Move(Vector2 offset);

    void Scale(int x, int y);
    void Scale(Vector2 scale);
};


#endif //KENAZENGINEGAME_CAMERA_H
