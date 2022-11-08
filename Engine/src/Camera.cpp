//
// Created by MasterKtos on 04.11.2022.
//

#include "Engine/Camera.h"
#include <SDL_render.h>
#include <iostream>

Camera::Camera(SDL_Renderer* renderer) {
    Position = std::pair<int, int>(0, 0);
    Renderer = renderer;
}

void Camera::MoveTo(int x, int y) {
    Position = std::pair<int, int>(x - screenDimensions.first/2,
                                   y - screenDimensions.second/2);
}

void Camera::Move(int x, int y) {
    Position.first += x;
    Position.second += y;
}

void Camera::Scale(int x, int y) {
    int errorCode = SDL_RenderSetScale(Renderer, x, y);
    std::cout << errorCode << " | " << SDL_GetError() << std::endl;
}
