//
// Created by MasterKtos on 22.11.2022.
//

#include "Ball.h"


Ball::Ball(KenazEngine::Texture &ballTexture, int id) : texture(ballTexture.GetCopy()),
                                                id(id),
                                                radius(1.0f),
                                                position(Vector2{0, 0}),
                                                speed(Vector2{0, 0}){
}

void Ball::SetRadius(float newRadius) { radius = newRadius; }
void Ball::SetPosition(float x, float y) { position = Vector2{x, y}; }
void Ball::SetPosition(Vector2 newPosition) { position = Vector2{newPosition.x, newPosition.y}; }
void Ball::SetSpeed(float x, float y) { speed = Vector2{x, y}; }

bool Ball::isInBounds(int widthMax, int heightMax) const {
    return (position.x > 0 && position.x < (float)widthMax &&
            position.y > 0 && position.y < (float)heightMax);
}

bool Ball::isColliding(Vector2 secondBallPos, float secondBallRadius) {
    return(position.Distance(secondBallPos) <= secondBallRadius + radius);
}

void Ball::Move() { texture.Move(speed.x, speed.y); }
void Ball::Show() { texture.Show(); }

int Ball::GetID() const { return id; }

Vector2 Ball::GetPosition() const { return Vector2(position.x, position.y); }
float Ball::GetRadius() const { return radius; }
