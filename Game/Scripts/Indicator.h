//
// Created by MasterKtos on 02.01.2023.
//

#ifndef KENAZENGINEGAME_INDICATOR_H
#define KENAZENGINEGAME_INDICATOR_H


#include "Engine/Texture.h"

class Indicator : public KenazEngine::Texture {
protected:
    float rotationDegrees;
public:
    Vector2 target;


    Indicator(SDL_Renderer *renderer, Camera *camera);

    void Rotate(float degrees);
    void PointTo(Vector2 dest);

    int Show() override;
};


#endif //KENAZENGINEGAME_INDICATOR_H
