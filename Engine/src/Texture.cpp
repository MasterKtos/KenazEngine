//
// Created by masterktos on 06.10.22.
//

#include "Engine/Texture.h"


namespace KenazEngine {

    Texture::Texture(SDL_Renderer* renderer, Camera *camera) {
        GameRenderer = renderer;
        this->camera = camera;
        Position = Vector2(0, 0);
        Size = Vector2(128, 128);
        Image = nullptr;
    }

    int Texture::Load(const std::string& fileName) {

        //LoadMapTextures image at specified path
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

        Size.x = loadedSurface->w;
        Size.y = loadedSurface->h;

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

    int Texture::Resize(float x, float y) {
        Size.x = x;
        Size.y = y;
        return 0;
    }

    int Texture::Move(float x, float y) {
        Position.x += x;
        Position.y += y;
        return 0;
    }

    int Texture::MoveTo(float x, float y) {
        Position.x = x;
        Position.y = y;
        return 0;
    }

    int Texture::Show() {
        SDL_Rect rect;
        rect.x = Position.x - Size.x/2 - camera->Position.x;
        rect.y = Position.y - Size.y/2 - camera->Position.y;
        rect.w = Size.x;
        rect.h = Size.y;
        SDL_RenderCopy( GameRenderer, Image, nullptr, &rect);
        return 0;
    }

    Vector2 Texture::GetPosition() {
        return Position;
    }

    Texture Texture::GetCopy() {
        Texture newTexture = Texture(GameRenderer, camera);
        newTexture.SetImage(Image);
        newTexture.MoveTo(Position.x, Position.y);
        newTexture.Resize(Size.x, Size.y);
        return newTexture;
    }

    void Texture::SetImage(SDL_Texture* image) {
        Image = image;
    }

    int Texture::Resize(Vector2 size) { return Resize(size.x, size.y); }
    int Texture::Move(Vector2 vector) { return Move(vector.x, vector.y); }
    int Texture::MoveTo(Vector2 position) { return MoveTo(position.x, position.y); }

    bool Texture::operator==(const Texture& texture) {
        return this->Image == texture.Image;
    }

    bool Texture::isValid() {
        return (GameRenderer != nullptr || camera != nullptr || Image != nullptr);
    }
}