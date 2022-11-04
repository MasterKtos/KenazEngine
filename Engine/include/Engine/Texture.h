//
// Created by masterktos on 06.10.22.
//

#ifndef SDLPROJECT_TEXTURE_H
#define SDLPROJECT_TEXTURE_H

#include "SDL.h"
#include <SDL_image.h>
#include <string>
#include <memory>


namespace KenazEngine {

    class Texture {
    private:
        SDL_Texture* Image;
        SDL_Renderer* GameRenderer;
        std::shared_ptr<std::pair<int16_t, int16_t>> Position;
        std::shared_ptr<std::pair<uint16_t, uint16_t>> Size;
    public:
        // Needs SDL_Renderer from KenazEngine
        explicit Texture(SDL_Renderer *renderer);

        int Load(const std::string& fileName);
        int Show();

        int Resize(int16_t x, int16_t y);
        int Move(int16_t x, int16_t y);
        int MoveTo(int16_t x, int16_t y);


        //for texture copy

        //TODO: replace with something better
        Texture GetCopy();
        SDL_Renderer* GetRenderer();
        SDL_Texture* GetImage();
        void SetImage(SDL_Texture* image);
        std::shared_ptr<std::pair<int16_t, int16_t>> GetPosition();
        std::shared_ptr<std::pair<uint16_t, uint16_t>> GetSize();
    };
}


#endif //SDLPROJECT_TEXTURE_H
