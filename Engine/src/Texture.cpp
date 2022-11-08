//
// Created by masterktos on 06.10.22.
//

#include "Engine/Texture.h"


namespace KenazEngine {

    Texture::Texture(SDL_Renderer* renderer, Camera *camera) {
        GameRenderer = renderer;
        this->camera = camera;
        Position = std::make_shared<std::pair<int16_t, int16_t>>(0, 0);
        Size = std::make_shared<std::pair<uint16_t, uint16_t>>(128, 128);
        Image = nullptr;
    }

    int Texture::Load(const std::string& fileName) {

        //LoadMap image at specified path
        std::string filePath;
        //TODO: get project directory
        filePath.append(SDL_GetBasePath())
                .append("../../Game/Textures/")
                .append(fileName);
        SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
        if(!loadedSurface)
        {
            printf( "Unable to load image %s! SDL_image Error: %s\n", fileName.c_str(), IMG_GetError() );
            return 1;
        }

        Size->first = loadedSurface->w;
        Size->second = loadedSurface->h;

        //Create texture from surface pixels
        Image = SDL_CreateTextureFromSurface( GameRenderer, loadedSurface );
        if(!Image)
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", fileName.c_str(), SDL_GetError() );
            return 2;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );

        return 0;
    }

    int Texture::Resize(int16_t x, int16_t y) {
        Size->first = x;
        Size->second = y;
        return 0;
    }

    int Texture::Move(int16_t x, int16_t y) {
        Position->first = Position->first + x;
        Position->second = Position->second + y;
        return 0;
    }

    int Texture::MoveTo(int16_t x, int16_t y) {
        Position->first = x;
        Position->second = y;
        return 0;
    }

    int Texture::Show() {
        SDL_Rect rect;
        rect.x = Position->first - Size->first/2 - camera->Position.first;
        rect.y = Position->second - Size->second/2 - camera->Position.second;
        rect.w = Size->first;
        rect.h = Size->second;
        SDL_RenderCopy( GameRenderer, Image, nullptr, &rect);
        return 0;
    }

    std::shared_ptr<std::pair<int16_t, int16_t>> Texture::GetPosition() {
        return Position;
    }

    Texture Texture::GetCopy() {
        Texture newTexture = Texture(GameRenderer, camera);
        newTexture.SetImage(Image);
        newTexture.MoveTo(Position->first, Position->second);
        newTexture.Resize(Size->first, Size->second);
        return newTexture;
    }

    void Texture::SetImage(SDL_Texture* image) {
        Image = image;
    }
}