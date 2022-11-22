//
// Created by MasterKtos on 22.11.2022.
//

#ifndef KENAZENGINEGAME_BALL_H
#define KENAZENGINEGAME_BALL_H

#include "Engine/Texture.h"

struct Vector2 {int x, y;};

class Ball {
private:
    int radius;
    Vector2 position;
    KenazEngine::Texture texture;

public:
    Ball(KenazEngine::Texture &ballTexture);
    void SetRadius(int newRadius);
    void SetPosition(int x, int y);
    void SetPosition(Vector2 newPosition);
};


#endif //KENAZENGINEGAME_BALL_H
