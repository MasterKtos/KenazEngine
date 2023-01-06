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

    if(speed != currentSpeed) {
        currentSpeed = Vector2::Lerp(currentSpeed, speed, speedLerp);
    }
    Vector2 speedMasked(
            collisionVector.x * currentSpeed.x >= 0 ? currentSpeed.x : 0,
            collisionVector.y * currentSpeed.y >= 0 ? currentSpeed.y : 0);
    texture->Move(speedMasked);

    //printf("%s\n", (currentSpeed + currentSpeed * collisionVector).toString().c_str());
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
    // Used to divide area around player to 8 parts
    // --------------------------------------------
    float regionSize = GetSize();

    std::unordered_map<Direction, Vector2> categorizedCollisions;
    DirectionMask dirMask;
    // Categorize collisions
    // ---------------------
    for( auto collision : collisions) {
        Vector2 diff = position - collision;
        printf("%f %s\t", regionSize, diff.toString().c_str());

        // Check if collision comes from direction
        //   where player is going ("in front" of player);
        // If so, skip checking such
        // ----------------------------------------------
        //if(diff.x * speed.x < 0 || diff.y * -speed.y < 0) continue;

        // Division looks like such:
        //
        //  NW \ N / NE  } regionSize/2
        //  W >  x  < E  } regionSize
        //  SW / S \ SE  } regionSize/2

        // N
        Direction direction;
        if(diff.y >= regionSize/2 && abs(diff.y)+5 >= abs(diff.x)) {
            /*if     (diff.x >  regionSize/2) { direction = Direction::NW; dirMask.NW = true; }
            else if(diff.x < -regionSize/2) { direction = Direction::NE; dirMask.NE = true; }
            else*/                            { direction = Direction::N; dirMask.N = true; }
        }
        // S
        else if(diff.y <= -regionSize/2 && abs(diff.y)+5 >= abs(diff.x)) {
            /*if     (diff.x >  regionSize/2) { direction = Direction::SW; dirMask.SW = true; }
            else if(diff.x < -regionSize/2) { direction = Direction::SE; dirMask.SE = true; }
            else*/                            { direction = Direction::S; dirMask.S = true; }
        }
        // E/W
        else {
            if(diff.x > 0) { direction = Direction::W; dirMask.W = true; }
            else           { direction = Direction::E; dirMask.E = true; }
        }
        categorizedCollisions.insert({direction, collision});
    }
    if(dirMask.N)  printf("N ");
    if(dirMask.NE) printf("NE ");
    if(dirMask.E)  printf("E ");
    if(dirMask.SE) printf("SE ");
    if(dirMask.S)  printf("S ");
    if(dirMask.SW) printf("SW ");
    if(dirMask.W)  printf("W ");
    if(dirMask.NW) printf("NW ");

    collisionVector = Vector2(0);
    if(dirMask.N) collisionVector.y += 1;
    if(dirMask.S) collisionVector.y -= 1;
    if(dirMask.E) collisionVector.x -= 1;
    if(dirMask.W) collisionVector.x += 1;

    // Edge cases
    //if(!dirMask.S && !dirMask.E && dirMask.SE) collisionVector.y -=1;

//    if(dirMask.NE) collisionVector += Vector2(-0.5f, 0.5f);
//    if(dirMask.SW && !dirMask.S) collisionVector += Vector2(0.5f, -0.5f);
//    if(dirMask.SE && !dirMask.S) collisionVector += Vector2(-0.5f, -0.5f);
//    if(dirMask.NW) collisionVector += Vector2(0.5f, 0.5f);

    printf("\t\t[%f, %f]\n", collisionVector.x, collisionVector.y);
}

Vector2 KenazEngine::Player::GetPosition() { return texture->GetPosition(); }
float KenazEngine::Player::GetSize() { return texture->GetScale(); }

//Vector2 KenazEngine::Player::GetCollisionDirection(Vector2 pos) {
//    Vector2 diff = texture->GetPosition() - pos;
//    diff = abs(diff.x) > abs(diff.y) ? Vector2(1, 0) : Vector2(0, 1);
//    return diff;
//}
