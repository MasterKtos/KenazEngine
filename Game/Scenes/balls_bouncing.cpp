#include <cmath>
#include <iostream>
#include "SDL.h"
#include "Engine/KenazEngine.h"
#include "../BallManager.h"

int balls_bouncing_run() {
    std::pair<int, int> screenSize = {800, 600};

    KenazEngine::KenazEngine Kenaz;

    // Initialize engine parameters
    Kenaz.SetTitle("KenazEngine Game");
    Kenaz.SetResolution(screenSize.first, screenSize.second);
    Kenaz.SetBackgroundColor(1, 8, 16);

    if(!Kenaz.Start()) return 1;

    KenazEngine::Texture* Fren = Kenaz.CreateTexture();
    Fren->Load("circle.png");
    Fren->Resize(32, 32);
    Fren->MoveTo(500, 400);

    BallManager ballManager;
    ballManager.CreateBalls(50, *Fren);
    ballManager.RandomizeBalls();

    SDL_Event event;

    printf("=============================\n|| [R] - toggle reflection ||\n|| [S] - toggle separation ||\n=============================\n\n");

    for (int i=0;;i++) {
        Kenaz.UpdateBegin();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return Kenaz.Quit();
            }
            if(event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_s:
                        ballManager.separationEnabled = !ballManager.separationEnabled;
                        printf("Separation: ");
                        printf(ballManager.separationEnabled? "ON\n" : "OFF\n");
                        break;
                    case SDLK_r:
                        ballManager.reflectionEnabled = !ballManager.reflectionEnabled;
                        printf("Reflection: ");
                        printf(ballManager.reflectionEnabled? "ON\n" : "OFF\n");
                        break;
                    default:
                        break;
                }
            }
        }

        ballManager.ShowBalls();

        ballManager.MoveBalls();
    }
}