//
// Created by masterktos on 27.12.22.
//

#include <vector>
#include "Engine/Player.h"

KenazEngine::Player::Player() : currentSpeed(0), speed(0), speedLerp(1) {}

void KenazEngine::Player::SetTexture(Texture* newTexture) { texture = newTexture; }

void KenazEngine::Player::Show() { if(texture) texture->Show(); }

void KenazEngine::Player::Move() {
    if(!texture) return;

    if(speed != currentSpeed) {
        currentSpeed = Vector2::Lerp(currentSpeed, speed, speedLerp);
    }
    texture->Move(currentSpeed + currentSpeed * collisionVector);

    printf("%s\n", collisionVector.toString().c_str());
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

void KenazEngine::Player::OnBoxCollide(Vector2 pos, float otherRadius) {
    if(pos == Vector2(0)) { collisionVector = pos; return; }

    Vector2 position = texture->GetPosition();
    float distance = position.Distance(pos);
    Vector2 normalVector = (position - pos)/distance;

    // Separation
    // ----------
    float moveScalar = GetSize()/2 + otherRadius - distance;
    printf("%f\t[%f, %f]\t", moveScalar, normalVector.x, normalVector.y);
    texture->Move(normalVector * moveScalar);

    // Reflection
    // ----------
    collisionVector += normalVector;
    collisionVector.Mask(normalVector);
    collisionVector.Clamp(1);
}

Vector2 KenazEngine::Player::GetPosition() { return texture->GetPosition(); }
float KenazEngine::Player::GetSize() { return texture->GetScale(); }

void KenazEngine::Player::AnalyzeCollisions(const std::vector<Vector2>& collisions) {
    Vector2 position = GetPosition();
    std::vector<std::pair<Vector2, Direction>> categorizedCollisions;
    // Categorize collisions
    // ---------------------
    for( auto collision : collisions) {
        Vector2 diff = position - collision;

        // Check if collision comes from direction
        //   where player is going ("in front" of player);
        // If so, skip checking such
        // ----------------------------------------------
        if(diff.x * speed.x < 0 || diff.y * speed.y < 0) continue;

        // UP
        if(diff.y >= 0) {
            // LEFT
            if(diff.x >= 0) {
                //categorizedCollisions.push_back({collision, Direction::})
            }
        }
    }
}

//Vector2 KenazEngine::Player::GetCollisionDirection(Vector2 pos) {
//    Vector2 diff = texture->GetPosition() - pos;
//    diff = abs(diff.x) > abs(diff.y) ? Vector2(1, 0) : Vector2(0, 1);
//    return diff;
//}
