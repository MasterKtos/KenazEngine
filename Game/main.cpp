#include "SDL2/SDL.h"
#include "Engine/KenazEngine.h"
#include "Engine/Map.h"

void Lerp(float &currPosX, float &currPosY, float destPosX, float destPosY, float lerpValue) {
    currPosX = currPosX + (destPosX - currPosX)*lerpValue;
    currPosY = currPosY + (destPosY - currPosY)*lerpValue;
}

int main(int argc, char *argv[]) {
    KenazEngine::KenazEngine Kenaz;

    // Initialize engine parameters
    Kenaz.SetTitle("SDL Project");
    Kenaz.SetResolution(800, 600);
    Kenaz.SetBackgroundColor(1, 8, 16);

    if(!Kenaz.Start()) return 1;

    KenazEngine::Texture* Player = Kenaz.CreateTexture();
    Player->Load("square.png");
    Player->Resize(32, 32);
    Player->MoveTo(32*5, 32*6);

    KenazEngine::Texture* Fren = Kenaz.CreateTexture();
    Fren->Load("circle.png");
    Fren->Resize(32, 32);
    Fren->MoveTo(400, 200);

    //TODO: change the way events are handled
    SDL_Event event;

    float playerMoveX;
    float playerMoveY;

    float playerCurrentMoveX;
    float playerCurrentMoveY;

    float frenPositionX;
    float frenPositionY;

    float frenCurrentPositionX;
    float frenCurrentPositionY;

    KenazEngine::Map map = KenazEngine::Map(32);
    map.LoadFloor(Fren);
    map.LoadWall(Player);
    map.LoadMap("../../map.txt");

    int i = 0;
    for (;;i++) {
        Kenaz.UpdateBegin();
        #pragma region Handle events
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
                //printf("KEYDOWN | %d \n", event.key.keysym.sym);
            }
            if(event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_DOWN: playerMoveY = 0; break;
                    case SDLK_LEFT:
                    case SDLK_RIGHT: playerMoveX = 0; break;
                }
                //printf("KEYUP | %d \n", event.key.keysym.sym);
            }
            if(event.type == SDL_MOUSEMOTION) {
                //printf("KEYMOTION [ %d | %d ] \n", event.motion.x, event.motion.y);
                frenPositionX = event.motion.x;
                frenPositionY = event.motion.y;
            }
        }
        #pragma endregion

        //Display stuff
        map.Show();
        Player->Show();
        Fren->Show();

        //Lerp(playerCurrentMoveX, playerCurrentMoveY,
        //     playerMoveX, playerMoveY, 0.05f);
        Player->Move(playerMoveX, playerMoveY);
        Lerp(frenCurrentPositionX, frenCurrentPositionY,
             frenPositionX, frenPositionY, 0.1f);
        Fren->MoveTo(frenCurrentPositionX, frenCurrentPositionY);
    }

    SDL_Quit();
    return 0;
}