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

void KenazEngine::Player::AnalyzeCollisions(
        const std::vector<Vector2>& collisions,
        float otherRadius) {
    // Reset collision vector if there are no collisions
    // -------------------------------------------------
    if(collisions.empty()) { collisionVector = Vector2(0); return; }
    printf("ENTER");

    Vector2 position = GetPosition();
    // Used to divide area around player to 8 parts
    // --------------------------------------------
    float regionSize = GetSize()/2;
    std::unordered_map<Direction, Vector2> categorizedCollisions;
    // Categorize collisions
    // ---------------------
    for( auto collision : collisions) {
        Vector2 diff = position - collision;

        // Check if collision comes from direction
        //   where player is going ("in front" of player);
        // If so, skip checking such
        // ----------------------------------------------
        if(diff.x * speed.x < 0 || diff.y * speed.y < 0) continue;

        // Division looks like such:
        //
        //  NW \ N / NE  } regionSize/2
        //  W >  x  < E  } regionSize
        //  SW / S \ SE  } regionSize/2

        // N
        Direction direction;
        if(diff.y >= regionSize/2) {
            if     (diff.x > regionSize/2) direction = Direction::NW;
            else if(diff.x < regionSize/2) direction = Direction::NE;
            else                           direction = Direction::N;
        }
        // S
        else if(diff.y <= regionSize/2) {
            if     (diff.x > regionSize/2) direction = Direction::SW;
            else if(diff.x < regionSize/2) direction = Direction::SE;
            else                           direction = Direction::S;
        }
        // E/W
        else {
            if(diff.x > 0) direction = Direction::W;
            else           direction = Direction::E;
        }
        categorizedCollisions.insert({direction, collision});
    }

    // if there's collision up, down, left or right,
    //  adjanced corner collisions are irrevelant
    // ---------------------------------------------
    if(categorizedCollisions.find(Direction::N) != categorizedCollisions.end())
    {
        if(categorizedCollisions.find(Direction::NE) != categorizedCollisions.end())
            categorizedCollisions.erase(Direction::NE);
        if(categorizedCollisions.find(Direction::NW) != categorizedCollisions.end())
            categorizedCollisions.erase(Direction::NW);
    }
    // there cannot be opposing directions present, hence "else"
    else if(categorizedCollisions.find(Direction::S) != categorizedCollisions.end())
    {
        if(categorizedCollisions.find(Direction::SE) != categorizedCollisions.end())
            categorizedCollisions.erase(Direction::SE);
        if(categorizedCollisions.find(Direction::SW) != categorizedCollisions.end())
            categorizedCollisions.erase(Direction::SW);
    }
    // Do the same for the sides
    if(categorizedCollisions.find(Direction::E) != categorizedCollisions.end())
    {
        if(categorizedCollisions.find(Direction::NE) != categorizedCollisions.end())
            categorizedCollisions.erase(Direction::NE);
        if(categorizedCollisions.find(Direction::SE) != categorizedCollisions.end())
            categorizedCollisions.erase(Direction::SE);
    }
    else if(categorizedCollisions.find(Direction::W) != categorizedCollisions.end())
    {
        if(categorizedCollisions.find(Direction::NW) != categorizedCollisions.end())
            categorizedCollisions.erase(Direction::NW);
        if(categorizedCollisions.find(Direction::SW) != categorizedCollisions.end())
            categorizedCollisions.erase(Direction::SW);
    }

    for(auto catCollision : categorizedCollisions) {
        OnBoxCollide(catCollision.second, otherRadius);
    }
}

Vector2 KenazEngine::Player::GetPosition() { return texture->GetPosition(); }
float KenazEngine::Player::GetSize() { return texture->GetScale(); }

//Vector2 KenazEngine::Player::GetCollisionDirection(Vector2 pos) {
//    Vector2 diff = texture->GetPosition() - pos;
//    diff = abs(diff.x) > abs(diff.y) ? Vector2(1, 0) : Vector2(0, 1);
//    return diff;
//}
