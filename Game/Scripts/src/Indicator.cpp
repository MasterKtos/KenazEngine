//
// Created by MasterKtos on 02.01.2023.
//

#include "../Indicator.h"

#include <cmath>

Indicator::Indicator(SDL_Renderer *renderer, Camera *camera)
        : Texture(renderer, camera), rotationDegrees(0) {}


void Indicator::Rotate(float degrees) {}

void Indicator::PointTo(Vector2 dest) {
    Vector2 delta = Position - dest;
    rotationDegrees = std::atan2(delta.y, delta.x) * 180 / M_PI;
}

int Indicator::Show() {
    //Set rendering space and render to screen
    SDL_Rect renderQuad{
            static_cast<int>(Position.x),
            static_cast<int>(Position.y),
            static_cast<int>(Size.x),
            static_cast<int>(Size.y) };

    //Render to screen
    SDL_RenderCopyEx(GameRenderer, Image,
                     nullptr, &renderQuad,
                     rotationDegrees, nullptr, SDL_FLIP_NONE );
}

Indicator& Indicator::operator=(KenazEngine::Texture *texture) {
    SetImage(texture->Image);
    MoveTo(texture->GetPosition());
    this->Resize(texture->Size);
    return *this;
}
