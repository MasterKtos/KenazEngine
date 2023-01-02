//
// Created by masterktos on 06.10.22.
//

#ifndef SDLPROJECT_TEXTURE_H
#define SDLPROJECT_TEXTURE_H

#include "SDL.h"
#include "Camera.h"
#include "Vector2.h"
#include <SDL_image.h>
#include <string>
#include <memory>


namespace KenazEngine {

    class Texture {
    protected:
        SDL_Renderer* GameRenderer;
        Camera* camera;
        Vector2 Position;
        Vector2 Size;
        SDL_Texture* Image;
    public:
        // Needs SDL_Renderer from KenazEngine
        Texture(SDL_Renderer *renderer, Camera *camera);

        int Load(const std::string& fileName);

        virtual int Show();

        int Resize(float x, float y);
        int Resize(Vector2 size);
        int Move(float x, float y);
        int Move(Vector2 vector);
        int MoveTo(float x, float y);
        int MoveTo(Vector2 position);


        // For texture copy
        // TODO: replace with something better
        Texture GetCopy();
        void SetImage(SDL_Texture* image);
        Vector2 GetPosition();

        bool operator==(const Texture& texture);
        bool isValid();
    };
}


#endif //SDLPROJECT_TEXTURE_H
