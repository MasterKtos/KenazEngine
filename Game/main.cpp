#include "SDL2/SDL.h"
#include "Engine/KenazEngine.h"

int main(int argc, char *argv[]) {
    KenazEngine::KenazEngine Kenaz;

    // Initialize engine parameters
    Kenaz.SetTitle("SDL Project");
    Kenaz.SetResolution(800, 600);
    Kenaz.SetBackgroundColor(1, 8, 16);

    if(!Kenaz.Start()) return 1;

    KenazEngine::Texture* Player = Kenaz.CreateTexture();
    Player->Load("square.png");
    Player->Resize(64, 64);
    Player->MoveTo(200, 300);

    KenazEngine::Texture* Fren = Kenaz.CreateTexture();
    Fren->Load("circle.png");
    Fren->Resize(64, 64);
    Fren->MoveTo(400, 200);

    //TODO: change the way events are handled
    SDL_Event event;
    float playerMoveX;
    float playerMoveY;
    float frenPositionX;
    float frenPositionY;

    int i = 0;
    for (;;i++) {
        Kenaz.UpdateBegin();
        //Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return Kenaz.Quit();
            }
            if(event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_UP: playerMoveY = -5; break;
                    case SDLK_DOWN: playerMoveY = 5; break;
                    case SDLK_LEFT: playerMoveX = -5; break;
                    case SDLK_RIGHT: playerMoveX = 5; break;
                }
                printf("KEYDOWN | %d \n", event.key.keysym.sym);
            }
            if(event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_DOWN: playerMoveY = 0; break;
                    case SDLK_LEFT:
                    case SDLK_RIGHT: playerMoveX = 0; break;
                }
                printf("KEYUP | %d \n", event.key.keysym.sym);
            }
            if(event.type == SDL_MOUSEMOTION) {
                printf("KEYMOTION [ %d | %d ] \n", event.motion.x, event.motion.y);
                frenPositionX = event.motion.x;
                frenPositionY = event.motion.y;
            }
        }

        //Display stuff
        Player->Show();
        Fren->Show();

        //ToDo: add Lerp to one object
        Player->Move(playerMoveX, playerMoveY);
        Fren->MoveTo(frenPositionX, frenPositionY);
    }


    SDL_Quit();
    return 0;
}
