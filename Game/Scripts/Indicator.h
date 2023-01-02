//
// Created by MasterKtos on 02.01.2023.
//

#ifndef KENAZENGINEGAME_INDICATOR_H
#define KENAZENGINEGAME_INDICATOR_H


#include "Engine/Texture.h"

class Indicator : KenazEngine::Texture {
protected:
    float rotationDegrees;

public:
    Indicator(SDL_Renderer *renderer, Camera *camera);

    void Rotate(float degrees);
    void PointTo(Vector2 dest);

    int Show() override;

    Indicator& operator=(KenazEngine::Texture* texture);
};


#endif //KENAZENGINEGAME_INDICATOR_H
