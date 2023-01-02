//
// Created by masterktos on 30.12.22.
//

#ifndef KENAZENGINEGAME_OVERLAY_H
#define KENAZENGINEGAME_OVERLAY_H

#include "Texture.h"

namespace KenazEngine {
    class Overlay : public Texture {
    public:
        Overlay(SDL_Renderer *pRenderer, Camera *pCamera);

        int Show() override;
    };
}

#endif //KENAZENGINEGAME_OVERLAY_H
