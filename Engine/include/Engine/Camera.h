//
// Created by MasterKtos on 04.11.2022.
//

#ifndef KENAZENGINEGAME_CAMERA_H
#define KENAZENGINEGAME_CAMERA_H


#include <utility>

class SDL_Renderer;

class Camera {
private:
    SDL_Renderer* Renderer;

public:
    Camera(SDL_Renderer* renderer);
    std::pair<int, int> Position;
    std::pair<int, int> screenDimensions;

    void MoveTo(int x, int y);
    void Move(int x, int y);

    void Scale(int x, int y);
};


#endif //KENAZENGINEGAME_CAMERA_H
