//
// Created by MasterKtos on 22.11.2022.
//

#ifndef KENAZENGINEGAME_BALL_H
#define KENAZENGINEGAME_BALL_H

#include "Engine/Texture.h"
#include "Vector2.h"

class Ball {
private:
    int id;
    float radius;
    Vector2 position;
    Vector2 speed;
    KenazEngine::Texture texture;

public:
    Ball(KenazEngine::Texture &ballTexture, int id);
    void SetRadius(float newRadius);
    void SetPosition(float x, float y);
    void SetPosition(Vector2 newPosition);
    void SetSpeed(float x, float y);

    bool isInBounds(int widthMax, int heightMax) const;
    bool isColliding(Vector2 secondBallPos, float secondBallRadius);

    void Move();
    void Show();

    int GetID() const;
    Vector2 GetPosition() const;
    float GetRadius() const;
};


#endif //KENAZENGINEGAME_BALL_H
