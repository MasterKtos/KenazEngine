//
// Created by masterktos on 27.12.22.
//

#ifndef KENAZENGINEGAME_PLAYER_H
#define KENAZENGINEGAME_PLAYER_H

#include "Vector2.h"
#include "Texture.h"
#include "JumpPhysics.h"

enum class Direction {
    N, NE, E, SE,
    S, SW, W, NW
};

struct DirectionMask {
    bool N = false, NE = false,
         E = false, SE = false,
         S = false, SW = false,
         W = false, NW = false;
};

namespace KenazEngine {
    class Player {
    private:
        Texture* texture;

        Vector2 collisionVector;

        void OnLanded();

    public:
        Vector2 posDelta;
        Vector2 currentSpeed;
        Vector2 speed;
        bool applyGravity;
        bool landed = false;
        JumpPhysics jumpPhysics;
        ///\note
        /// Value range: \<0, 1>  0 - max lerp, 1 - no lerp
        float speedLerp;

        Player();

        void SetTexture(Texture* newTexture);
        void Show();
        void Move(float deltaTime);
        void Jump();
        void OnCircleCollide(Vector2 pos);
        void OnBoxCollide(Vector2 pos, float otherRadius);

        void AnalyzeCollisions(
                const std::vector<Vector2>& collisions,
                float otherRadius);

        Vector2 GetPosition();
        float GetSize();
    };
}

#endif //KENAZENGINEGAME_PLAYER_H
