//
// Created by masterktos on 06.10.22.
//

#include "Engine/Texture.h"


namespace KenazEngine {

    Texture::Texture(SDL_Renderer* renderer) {
        GameRenderer = renderer;
        Position = std::make_shared<std::pair<int16_t, int16_t>>(0, 0);
        Size = std::make_shared<std::pair<uint16_t, uint16_t>>(128, 128);
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
        SDL_RenderCopy( GameRenderer, Image, nullptr,
                        new SDL_Rect { Position->first - Size->first/2, Position->second - Size->second/2,
                                                Size->first, Size->second });
        return 0;
    }

    SDL_Renderer *Texture::GetRenderer() {
        return GameRenderer;
    }

    SDL_Texture *Texture::GetImage() {
        return Image;
    }

    std::shared_ptr<std::pair<int16_t, int16_t>> Texture::GetPosition() {
        std::shared_ptr<std::pair<int16_t, int16_t>> copyPos;
        copyPos->first = Position->first;
        copyPos->second = Position->second;
        return copyPos;
    }

    std::shared_ptr<std::pair<uint16_t, uint16_t>> Texture::GetSize() {
        std::shared_ptr<std::pair<uint16_t, uint16_t>> copySize;
        copySize->first = Size->first;
        copySize->second = Size->second;
        return copySize;
    }

    Texture Texture::GetCopy() {
        Texture newTexture = Texture(GameRenderer);
        newTexture.SetImage(Image);
        newTexture.MoveTo(Position->first, Position->second);
        newTexture.Resize(Size->first, Size->second);
        return newTexture;
    }

    void Texture::SetImage(SDL_Texture* image) {
        Image = image;
    }
}