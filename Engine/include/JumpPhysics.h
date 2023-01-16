//
// Created by masterktos on 16.01.23.
//

#ifndef KENAZENGINEGAME_JUMPPHYSICS_H
#define KENAZENGINEGAME_JUMPPHYSICS_H

class JumpPhysics {
private:
    int fullJumpCount = 0;
    int jumpCount = 0;

    float Gravity() { return -2*height/(timeToMax*timeToMax) * deltaTime; }
    float InitialSpeed() { return 2*height/timeToMax; }
public:
    // Set up these values
    float height;
    float timeToMax;

    // Update every time player moves
    float deltaTime;
    float currentSpeedY;

    // Modifiers
    // ---------
    // Fast falling
    bool isFastFalling = false;
    float fastFallingMultiplier = 2;

    // Double Jump
    int maxFullJumpCount = 3;

    // Controlled jump
    bool isControlledJump = false;
    int controlledJumpSteps = 20;


    JumpPhysics() : height(100), timeToMax(0.4), deltaTime(0) {}

    float GetGravity() {
        if(isFastFalling && currentSpeedY < 0) {
            return Gravity() * fastFallingMultiplier;
        }
        return Gravity();
    }

    float GetInitialSpeed() {
        if(isControlledJump) {
            if(controlledJumpSteps > jumpCount) {
                jumpCount++;
                return 0.7 * InitialSpeed() / ((float) controlledJumpSteps / 2);
            }
        }
        else if(fullJumpCount < maxFullJumpCount &&
                currentSpeedY < 0) {
            fullJumpCount++;
            printf("siema\n\n\n");
            return InitialSpeed() - currentSpeedY;
        }
        return 0;
    }

    float GetPositionChange() {
        return 0.5f * Gravity() * deltaTime * deltaTime;
    }

    void Reset() {
        jumpCount = 0;
        fullJumpCount = 0;
    }
};

#endif //KENAZENGINEGAME_JUMPPHYSICS_H
