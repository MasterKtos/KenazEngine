//
// Created by masterktos on 27.12.22.
//

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
