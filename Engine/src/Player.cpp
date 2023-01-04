//
// Created by masterktos on 27.12.22.
//

#include <vector>
#include "Engine/Player.h"

KenazEngine::Player::Player() : currentSpeed(0), speed(0), lerp(1) {}

void KenazEngine::Player::SetTexture(Texture* newTexture) {
    texture = newTexture;
}

void KenazEngine::Player::Show() {
    if(texture) texture->Show();
}

void KenazEngine::Player::Move() {
    if(!texture) return;

    if(speed != currentSpeed) {
        currentSpeed = Vector2::Lerp(currentSpeed, speed, lerp);
    }
    texture->Move(currentSpeed);
}

Vector2 KenazEngine::Player::GetPosition() {
    return texture->GetPosition();
}

void KenazEngine::Player::OnCircleCollide(Vector2 pos) {
    Vector2 position = texture->GetPosition();
    float distance = position.Distance(pos);
    Vector2 normalVector = (position - pos)/distance;

    //printf("%s\n", normalVector.toString().c_str());

    // Separation
    // ----------
    //texture->Move(-normalVector * (radius*1.5 - distance));
    texture->Move(normalVector);

    // Reflection
    // ----------
    float dotProduct = 2*(currentSpeed.x*normalVector.x + currentSpeed.y*normalVector.y);
    //currentSpeed -= (normalVector * dotProduct)/2;
    currentSpeed -= currentSpeed * 1.1f;
}

void KenazEngine::Player::OnBoxCollide(Vector2 pos) {
    Vector2 position = texture->GetPosition();
    float distance = position.Distance(pos);
    Vector2 normalVector = (position - pos)/distance;

    //printf("%s\n", normalVector.toString().c_str());

    // Separation
    // ----------
    //texture->Move(-normalVector * (radius*1.5 - distance));
    texture->Move(normalVector);

    // Reflection
    // ----------
    float dotProduct = 2*(currentSpeed.x*normalVector.x + currentSpeed.y*normalVector.y);
    //currentSpeed -= (normalVector * dotProduct)/2;
    currentSpeed -= currentSpeed * 1.1f;
}

float KenazEngine::Player::GetSize() {
    return texture->GetScale();
}

//Vector2 KenazEngine::Player::GetCollisionDirection(Vector2 pos) {
//    Vector2 diff = texture->GetPosition() - pos;
//    diff = abs(diff.x) > abs(diff.y) ? Vector2(1, 0) : Vector2(0, 1);
//    return diff;
//}
