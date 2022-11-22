//
// Created by MasterKtos on 22.11.2022.
//

#include "Ball.h"


Ball::Ball(KenazEngine::Texture &ballTexture) : texture(ballTexture.GetCopy()){
    radius = 1.0f;
    position = Vector2{0, 0};
}

void Ball::SetRadius(int newRadius) { radius = newRadius; }
void Ball::SetPosition(int x, int y) { position = Vector2{x, y}; }
void Ball::SetPosition(Vector2 newPosition) { position = Vector2{newPosition.x, newPosition.y}; }
