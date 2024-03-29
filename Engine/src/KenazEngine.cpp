//
// Created by masterktos on 05.10.22.
//

#include "Engine/KenazEngine.h"
#include "Engine/Overlay.h"
#include "../../Game/Scripts/IconsUI.h"

#include <memory>
#include <utility>
#include <iostream>
#include <chrono>

namespace KenazEngine {
    KenazEngine::KenazEngine() {
        Resolution = std::make_shared<std::pair<uint16_t, uint16_t>>(640, 480);
        Framerate = 120;
    }

    #pragma region INITIALIZATION
    bool KenazEngine::SetResolution(int x, int y) {
        if(x < 0 || y < 0) return false;

        Resolution->first = x;
        Resolution->second = y;
        return true;
    }

    bool KenazEngine::SetTitle(std::string title) {
        Title = std::move(title);
        return true;
    }

    bool KenazEngine::SetBackgroundColor(int r, int g, int b) {
        if(r < 0 || r > 255 ||
           g < 0 || g > 255 ||
           b < 0 || b > 255)
            return false;
        BackgroundColor = Color(r, g, b);
        return true;
    }

    bool KenazEngine::KenazEngine::Start() {
        //if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            return false;
        }

        Window = SDL_CreateWindow(Title.c_str(),
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  Resolution->first, Resolution->second,
                                  SDL_WINDOW_SHOWN);
        if (Window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return false;
        }

        Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_SOFTWARE);
        SDL_SetRenderDrawColor(Renderer,
                               BackgroundColor.r, BackgroundColor.g, BackgroundColor.b,
                               SDL_ALPHA_OPAQUE);

        //Initialize JPG loading
        if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            return false;
        }

        Background = SDL_CreateTextureFromSurface(Renderer,
                                                  SDL_CreateRGBSurface(0,
                                                                       Resolution->first,
                                                                       Resolution->second,
                                                                       32,
                                                                       BackgroundColor.r,
                                                                       BackgroundColor.g,
                                                                       BackgroundColor.b,
                                                                       1));
        SDL_ShowCursor(SDL_DISABLE);
        camera = new Camera(Renderer);
        camera->screenDimensions.x = Resolution->first;
        camera->screenDimensions.y = Resolution->second;
        //camera->MoveTo(100, 100);

        cameraScale.first = 1.0f;
        cameraScale.second = 1.0f;

        return true;
    }
    #pragma endregion

    int KenazEngine::UpdateBegin(float deltaTime) {
        SDL_RenderPresent(Renderer);
        if (deltaTime < 0.016) {
            SDL_Delay(16 - deltaTime * 1000);
        }
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, Background, nullptr, nullptr);

        //SDL_RenderSetScale(Renderer, cameraScale.first, cameraScale.second);
        return 0;
    }

    int KenazEngine::Quit() {
        SDL_DestroyWindow(Window);
        return 0;
    }

    // Initializes Texture object
    // TODO: All created textures are automatically added to engine
    //  and can be displayed by KenazEngine.ShowTextures()
    Texture *KenazEngine::CreateTexture() {
        texturesToShow.push_back(new Texture(Renderer, camera));
        return texturesToShow.back();
    }
    std::shared_ptr<Overlay> KenazEngine::CreateOverlay() {
        return std::make_shared<Overlay>(Renderer, camera);
    }

    std::shared_ptr<Indicator> KenazEngine::CreateIndicator() {
        return std::make_shared<Indicator>(Renderer, camera);
    }
    std::shared_ptr<IconsUI> KenazEngine::CreateIcon() {
        return std::make_shared<IconsUI>(Renderer, camera);
    }
}