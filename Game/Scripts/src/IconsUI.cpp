//
// Created by masterktos on 18.01.23.
//

#include "../IconsUI.h"

int IconsUI::Show() {
    SDL_Rect rect;
    rect.x = Position.x - Size.x/2;
    rect.y = Position.y - Size.y/2;
    rect.w = Size.x;
    rect.h = Size.y;
    SDL_RenderCopy( GameRenderer, Image, nullptr, &rect);
    return 0;
}

IconsUI::IconsUI(SDL_Renderer *renderer, Camera *camera) : Texture(renderer, camera) {}
