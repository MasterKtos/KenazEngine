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

void Ball::SetRadius(float newRadius) { radius = newRadius; texture.Resize(radius*2, radius*2); }
void Ball::SetPosition(float x, float y) { position = Vector2{x, y}; texture.MoveTo(x, y); }
void Ball::SetPosition(Vector2 newPosition) { position = Vector2{newPosition.x, newPosition.y}; }
void Ball::SetSpeed(float x, float y) { speed = Vector2{x, y}; }

void Ball::Reflect(Vector2 normalVector) {
    float dotProduct = 2*(speed.x*normalVector.x + speed.y*normalVector.y);
    speed = speed - Vector2{normalVector.x * dotProduct, normalVector.y * dotProduct};
}

void Ball::CheckBounds(int widthMax, int heightMax) {
    if(!(position.x > radius && position.x < (float)widthMax - radius)) {
        speed.x = -speed.x;
        position.x = position.x < radius ? radius : widthMax-radius;
    }
    if(!(position.y > radius && position.y < (float)heightMax - radius)) {
        speed.y = -speed.y;
        position.y = position.y < radius ? radius : heightMax-radius;
    }
}

bool Ball::isColliding(Vector2 secondBallPos, float secondBallRadius) {
    float dist = position.Distance(secondBallPos);
    return (dist <= secondBallRadius + radius);
}

void Ball::Move() {
    position = position + speed;
    texture.MoveTo(position.x, position.y);
}
void Ball::Show() { texture.Show(); }

int Ball::GetID() const { return id; }

Vector2 Ball::GetPosition() const { return Vector2(position.x, position.y); }
float Ball::GetRadius() const { return radius; }

void Ball::OnCollide(Vector2 pos, float r, bool reflection, bool separation) {
    float distance = position.Distance(pos);
    Vector2 normalVector = (position - pos)/distance;
    if(separation) position = position + normalVector * (radius+r - distance);
    if(reflection) Reflect(normalVector);
}
