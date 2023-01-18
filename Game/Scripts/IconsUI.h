//
// Created by masterktos on 18.01.23.
//

#ifndef KENAZENGINEGAME_ICONSUI_H
#define KENAZENGINEGAME_ICONSUI_H


#include "Engine/Texture.h"

class IconsUI : public KenazEngine::Texture {
public:
    IconsUI(SDL_Renderer *renderer, Camera *camera);

    int Show() override;
};


#endif //KENAZENGINEGAME_ICONSUI_H
