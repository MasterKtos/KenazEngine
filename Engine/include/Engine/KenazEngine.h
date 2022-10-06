#ifndef SDLPROJECT_KENAZENGINE_H
#define SDLPROJECT_KENAZENGINE_H

#include <memory>
#include <cstdint>
#include <utility>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>
#include "Texture.h"

namespace KenazEngine {

    struct Color {
        uint8_t r, g, b;
        Color(uint8_t red, uint8_t green, uint8_t blue):
            r(red), g(green), b(blue) {}
        Color(): r(0), g(0), b(0) {}
    };

    class KenazEngine {
    private:
        std::shared_ptr<std::pair<uint16_t, uint16_t>> Resolution;
        Color BackgroundColor;
        std::string Title;

    private:
        SDL_Window* Window;
        SDL_Renderer* Renderer;
        SDL_Texture* Background;
        Texture* TestTexture;

    public:
        explicit KenazEngine();

        // call before init
        bool SetResolution(int x, int y);
        bool SetTitle(std::string title);
        bool SetBackgroundColor(int r, int g, int b);

        bool Start();
        int Update();

        Texture* CreateTexture();
    };

}

#endif //SDLPROJECT_KENAZENGINE_H
