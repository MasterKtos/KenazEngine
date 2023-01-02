//
// Created by MasterKtos on 04.11.2022.
//

#include "Engine/Camera.h"
#include <SDL_render.h>
#include <iostream>

Camera::Camera(SDL_Renderer* renderer) {
    Position = Vector2(0, 0);
    Renderer = renderer;
}

void Camera::MoveTo(int x, int y) {
    Position = Vector2(x - screenDimensions.x/2,
                       y - screenDimensions.y/2);
}

void Camera::Move(int x, int y) {
    Position.x += x;
    Position.y += y;
}

void Camera::Scale(int x, int y) {
    int errorCode = SDL_RenderSetScale(Renderer, x, y);
    std::cout << errorCode << " | " << SDL_GetError() << std::endl;
}

void Camera::MoveTo(Vector2 position) { MoveTo(position.x, position.y); }
void Camera::Move(Vector2 offset) { Move(offset.x, offset.y); }
void Camera::Scale(Vector2 scale) { Scale(scale.x, scale.y); }
