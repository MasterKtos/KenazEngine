//
// Created by masterktos on 27.12.22.
//

#include <vector>
#include <unordered_map>
#include "Engine/Player.h"

KenazEngine::Player::Player()
        : currentSpeed(0), speed(0), speedLerp(1),
          jumpCount(0), maxJumpCount(1) {}

void KenazEngine::Player::SetTexture(Texture* newTexture) { texture = newTexture; }

void KenazEngine::Player::Show() { if(texture) texture->Show(); }

void KenazEngine::Player::Move(float deltaTime) {
    if(!texture) return;

    posDelta = GetPosition();
    jumpPhysics.deltaTime = deltaTime;

    // Player not on ground
    // --------------------
    if(collisionVector.y >= 0) {
        speed.y -= jumpPhysics.Gravity() * deltaTime;
    }

    // Lerp only x speed
    // -----------------
    if(speed.x != currentSpeed.x) {
        currentSpeed = Vector2::Lerp(currentSpeed, Vector2(speed.x, currentSpeed.y), speedLerp);
    }

    texture->Move(currentSpeed + currentSpeed*collisionVector);
    currentSpeed.y += speed.y * deltaTime + jumpPhysics.GetPositionChange();

//    printf("Speed:\t\t\t%s\n", (speed).toString().c_str());
    posDelta -= GetPosition();
//    printf("Current speed:\t%s\n", (currentSpeed).toString().c_str());
}

void KenazEngine::Player::Jump() {
    if(collisionVector.y > 0 || jumpCount >= maxJumpCount) return;

    speed.y -= jumpPhysics.InitialSpeed();
//    printf("\tInitial speed: %f\n", jumpPhysics.InitialSpeed());
//    printf("\tGravity: %f\n", jumpPhysics.Gravity());
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
    //collisionVector += normalVector;
    //collisionVector.Mask(normalVector);
    //collisionVector.Clamp(1);
}

void KenazEngine::Player::AnalyzeCollisions(
        const std::vector<Vector2>& collisions,
        float otherRadius) {
    // Reset collision vector if there are no collisions
    // -------------------------------------------------
    if(collisions.empty()) {
        collisionVector = Vector2(0); landed = false; return;
    }

    Vector2 position = GetPosition();

    std::unordered_map<Direction, Vector2> categorizedCollisions;
    DirectionMask dirMask;
    // Categorize collisions
    // ---------------------
    for( auto collision : collisions) {
        Vector2 diff = position - collision;
        // printf("%f %s\t", regionSize, diff.toString().c_str());

        // ==========================================
        //              BELOW IS OBSOLETE
        //      Now it only divides to N, E, S, W
        // ==========================================
        // Division looks like such:
        //
        //  NW \ N / NE  } regionSize/2
        //  W >  x  < E  } regionSize
        //  SW / S \ SE  } regionSize/2

        // N
        if(diff.y > 0 && abs(diff.y)+5 >= abs(diff.x)) {
            // First collision detected in that direction
            //if(!dirMask.N && collisionVector.y < 0)
            //    texture->Move(0, -diff.y + GetSize()/2 + otherRadius);
            dirMask.N = true;
            if(abs(diff.y) < GetSize()/2 + otherRadius)
                texture->Move(0, -(diff.y + GetSize()/2 + otherRadius));
        }
        // S
        else if(diff.y < 0 && abs(diff.y)+5 >= abs(diff.x)) {
            //if(!dirMask.S && collisionVector.y > 0)
            //    texture->Move(0, -diff.y - GetSize()/2 - otherRadius);
            dirMask.S = true;
            if(abs(diff.y) < GetSize()/2 + otherRadius)
                texture->Move(0, -(diff.y + GetSize()/2 + otherRadius));
        }
        // E/W
        else {
            if(diff.x > 0) {
                //if(!dirMask.W && collisionVector.x < 0)
                //    texture->Move( -diff.y - GetSize()/2 - otherRadius, 0);
                dirMask.W = true;
                if(abs(diff.x) < GetSize()/2 + otherRadius)
                    texture->Move(-(diff.x + GetSize()/2 + otherRadius), 0);
            }
            else {
                //if(!dirMask.E && collisionVector.x > 0)
                //    texture->Move( -diff.y - GetSize()/2 - otherRadius, 0);
                dirMask.E = true;
                if(abs(diff.x) < GetSize()/2 + otherRadius)
                    texture->Move(-(diff.x + GetSize()/2 + otherRadius), 0);
            }
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
    //printf("\n");
    #pragma endregion

    // Player landed
    // -------------
    if(dirMask.S && !landed) OnLanded();
    if(dirMask.N && currentSpeed.y < 0) {
        speed.y = 0; currentSpeed.y = 0; }

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

void KenazEngine::Player::OnLanded() {
    landed = true;
//    printf("lmao\n\n\n\n\n");
    speed.y = 0;
    currentSpeed.y = 0;
    jumpCount = 0;
}
