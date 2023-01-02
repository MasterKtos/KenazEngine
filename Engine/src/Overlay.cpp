//
// Created by masterktos on 30.12.22.
//

#include "Engine/Overlay.h"

KenazEngine::Overlay::Overlay(SDL_Renderer *pRenderer,
                              Camera *pCamera) :
        Texture(pRenderer, pCamera) {
}

int KenazEngine::Overlay::Show() {
    SDL_Rect rect;
    rect.x = Position.x - Size.x/2;
    rect.y = Position.y - Size.y/2;
    rect.w = Size.x;
    rect.h = Size.y;
    SDL_RenderCopy( GameRenderer, Image, nullptr, &rect);
    return 0;
}
