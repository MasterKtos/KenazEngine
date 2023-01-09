//
// Created by masterktos on 27.12.22.
//

#include <vector>
#include <unordered_map>
#include "Engine/Player.h"

KenazEngine::Player::Player() : currentSpeed(0), speed(0), speedLerp(1) {}

void KenazEngine::Player::SetTexture(Texture* newTexture) { texture = newTexture; }

void KenazEngine::Player::Show() { if(texture) texture->Show(); }

void KenazEngine::Player::Move() {
    if(!texture) return;
    printf("%[%f, %f]\n", currentSpeed.x, currentSpeed.y);

    if(speed != currentSpeed) {
        currentSpeed = Vector2::Lerp(currentSpeed, speed, speedLerp);
    }
    texture->Move(currentSpeed + currentSpeed*collisionVector);

    //printf("%s\n", (currentSpeed + currentSpeed * collisionVector).toString().c_str());
}

void KenazEngine::Player::Jump() {
    currentSpeed.y = jumpForce;
}

// ==========
// Collisions
// ==========

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
    Vector2 position = texture->GetPosition();
    float distance = position.Distance(pos);
    Vector2 normalVector = (position - pos)/distance;

    // Separation
    // ----------
    float moveScalar = GetSize()/2 + otherRadius - distance;
    //printf("%f\t[%f, %f]\t", moveScalar, normalVector.x, normalVector.y);
    texture->Move(normalVector * moveScalar);

    // Reflection
    // ----------
    collisionVector += normalVector;
    collisionVector.Mask(normalVector);
    collisionVector.Clamp(1);
}

void KenazEngine::Player::AnalyzeCollisions(
        const std::vector<Vector2>& collisions,
        float otherRadius) {
    // Reset collision vector if there are no collisions
    // -------------------------------------------------
    if(collisions.empty()) { collisionVector = Vector2(0); return; }

    Vector2 position = GetPosition();

    std::unordered_map<Direction, Vector2> categorizedCollisions;
    DirectionMask dirMask;
    // Categorize collisions
    // ---------------------
    for( auto collision : collisions) {
        Vector2 diff = position - collision;
        // printf("%f %s\t", regionSize, diff.toString().c_str());

        // =================================
        // BELOW IS OBSOLETE
        // Now it only divides to N, E, S, W
        // =================================
        // Division looks like such:
        //
        //  NW \ N / NE  } regionSize/2
        //  W >  x  < E  } regionSize
        //  SW / S \ SE  } regionSize/2

        // N
        if     (diff.y > 0 && abs(diff.y)+5 >= abs(diff.x)) dirMask.N = true;
        // S
        else if(diff.y < 0 && abs(diff.y)+5 >= abs(diff.x)) dirMask.S = true;
        // E/W
        else {
            if(diff.x > 0) dirMask.W = true;
            else           dirMask.E = true;
        }
    }
    #pragma region  Mask print
    //if(dirMask.N)  printf("N ");
    //if(dirMask.NE) printf("NE ");
    //if(dirMask.E)  printf("E ");
    //if(dirMask.SE) printf("SE ");
    //if(dirMask.S)  printf("S ");
    //if(dirMask.SW) printf("SW ");
    //if(dirMask.W)  printf("W ");
    //if(dirMask.NW) printf("NW ");
    #pragma endregion

    collisionVector = Vector2(0);
    if(dirMask.N) collisionVector.y += 1;
    if(dirMask.S) collisionVector.y -= 1;
    if(dirMask.E) collisionVector.x -= 1;
    if(dirMask.W) collisionVector.x += 1;

    collisionVector = Vector2(
            collisionVector.x * currentSpeed.x >= 0 ? 0 : -1,
            collisionVector.y * currentSpeed.y >= 0 ? 0 : -1);

    //printf("\t\t[%f, %f]\n", collisionVector.x, collisionVector.y);
}

Vector2 KenazEngine::Player::GetPosition() { return texture->GetPosition(); }
float KenazEngine::Player::GetSize() { return texture->GetScale(); }
