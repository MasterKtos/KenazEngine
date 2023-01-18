#ifndef SDLPROJECT_KENAZENGINE_H
#define SDLPROJECT_KENAZENGINE_H

#include <memory>
#include <cstdint>
#include <utility>
#include <SDL.h>
#include <string>
#include <vector>

#include "Texture.h"
#include "Camera.h"
#include "Overlay.h"
#include "../../../Game/Scripts/Indicator.h"
#include "../../../Game/Scripts/IconsUI.h"

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
        std::vector<Texture*> texturesToShow;
        Color BackgroundColor;
        std::string Title;
        uint8_t Framerate;

        SDL_Window* Window;
        SDL_Renderer* Renderer;
        SDL_Texture* Background;

    public:
        Camera* camera;
        //TODO: change pls
        std::pair<float, float> cameraScale;

        explicit KenazEngine();

        // call before init
        bool SetResolution(int x, int y);
        bool SetTitle(std::string title);
        bool SetBackgroundColor(int r, int g, int b);

        bool Start();
        int UpdateBegin(float deltaTime);
        int Quit();

        Texture* CreateTexture();
        std::shared_ptr<Overlay> CreateOverlay();
        std::shared_ptr<Indicator> CreateIndicator();
        std::shared_ptr<IconsUI> CreateIcon();
    };

}

#endif //SDLPROJECT_KENAZENGINE_H
