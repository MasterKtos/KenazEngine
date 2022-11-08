#include <iostream>
#include "SDL.h"
#include "Engine/KenazEngine.h"
#include "Engine/Map.h"
#include "Engine/Joystick.h"

void Lerp(float &currPosX, float &currPosY, float destPosX, float destPosY, float lerpValue) {
    currPosX = currPosX + (destPosX - currPosX)*lerpValue;
    currPosY = currPosY + (destPosY - currPosY)*lerpValue;
}

int Distance(int first, int second) {
    return (second - first);
}

std::pair<int, int> MiddlePoint(std::shared_ptr<std::pair<int16_t, int16_t>> firstPoint,
                                std::shared_ptr<std::pair<int16_t, int16_t>> secondPoint) {
    return {
            firstPoint->first + Distance(firstPoint->first, secondPoint->first)/2,
            firstPoint->second + Distance(firstPoint->second, secondPoint->second)/2
    };
}

int main(int argc, char *argv[]) {
    KenazEngine::KenazEngine Kenaz;
    Joystick joystick;

    // Initialize engine parameters
    Kenaz.SetTitle("SDL Project");
    Kenaz.SetResolution(800, 600);
    Kenaz.SetBackgroundColor(1, 8, 16);

    if(!Kenaz.Start()) return 1;

    joystick.Connect();

    KenazEngine::Texture* Player = Kenaz.CreateTexture();
    Player->Load("square.png");
    Player->Resize(32, 32);
    Player->MoveTo(400, 300);

    KenazEngine::Texture* Fren = Kenaz.CreateTexture();
    Fren->Load("circle.png");
    Fren->Resize(32, 32);
    Fren->MoveTo(500, 300);

    //TODO: change the way events are handled
    SDL_Event event;

    float playerMoveX;
    float playerMoveY;

    float moveRegion = 50;
    std::pair<uint16_t, uint16_t> screenCentre(400, 300);
    float playerPosX = 0;

    float frenMoveX = 0;
    float frenMoveY = 0;

    float frenCurrentMoveX = 0;
    float frenCurrentMoveY = 0;

    KenazEngine::Texture* Floor = Kenaz.CreateTexture();
    Floor->Load("floor.png");

    KenazEngine::Texture* WallH = Kenaz.CreateTexture();
    WallH->Load("wall_horizontal.png");

    KenazEngine::Texture* WallV = Kenaz.CreateTexture();
    WallV->Load("wall_vertical.png");

    KenazEngine::Texture* WallC = Kenaz.CreateTexture();
    WallC->Load("wall_connector.png");

    KenazEngine::Map map = KenazEngine::Map(32);
    map.LoadTile('f', Floor);
    map.LoadTile('h', WallH);
    map.LoadTile('v', WallV);
    map.LoadTile('c', WallC);
    map.LoadMap("../../map.txt");

    for (int i=0;;i++) {
        Kenaz.UpdateBegin();
        #pragma region Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return Kenaz.Quit();
            }
            if(event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    // player 1
                    case SDLK_UP: playerMoveY = -5; break;
                    case SDLK_DOWN: playerMoveY = 5; break;
                    case SDLK_LEFT: playerMoveX = -5; break;
                    case SDLK_RIGHT: playerMoveX = 5; break;
                }
                switch(event.key.keysym.sym) {
                    // player 2
                    case SDLK_w: frenMoveY = -5; break;
                    case SDLK_s: frenMoveY = 5; break;
                    case SDLK_a: frenMoveX = -5; break;
                    case SDLK_d: frenMoveX = 5; break;
                }
                //printf("KEYDOWN | %d \n", event.key.keysym.sym);
            }
            if(event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                    // player 1
                    case SDLK_UP:
                    case SDLK_DOWN: playerMoveY = 0; break;
                    case SDLK_LEFT:
                    case SDLK_RIGHT: playerMoveX = 0; break;
                }
                switch(event.key.keysym.sym) {
                    // player 2
                    case SDLK_w:
                    case SDLK_s: frenMoveY = 0; break;
                    case SDLK_a:
                    case SDLK_d: frenMoveX = 0; break;
                }
                //printf("KEYUP | %d \n", event.key.keysym.sym);
            }
            if(event.type == SDL_JOYAXISMOTION) {
                switch(joystick.HandleInput(event)) {
                    case MOVE_UP: frenMoveY = -5; break;
                    case MOVE_DOWN: frenMoveY = 5; break;
                    case STOP_VERTICAL: frenMoveY = 0; break;
                    case MOVE_LEFT: frenMoveX = -5; break;
                    case MOVE_RIGHT: frenMoveX = 5; break;
                    case STOP_HORIZONTAL: frenMoveX = 0; break;
                    case NONE: frenMoveX = 0; frenMoveY = 0; break;
                }
            }
            // capture mouse movement
            //if(event.type == SDL_MOUSEMOTION) {
            //    //printf("KEYMOTION [ %d | %d ] \n", event.motion.x, event.motion.y);
            //    frenPositionX = event.motion.x;frenMoveY
            //    frenPositionY = event.motion.y;
            //}
        }
        #pragma endregion

        // Set render scale
        if(abs(Distance(Player->GetPosition()->first, Fren->GetPosition()->first)) > Kenaz.camera->screenDimensions.first) {
            float scaleX = Kenaz.camera->screenDimensions.first;
            scaleX /= (float) abs(Distance(Player->GetPosition()->first,
                                           Fren->GetPosition()->first));
            std::cout << scaleX << std::endl;
            Kenaz.cameraScale.first = scaleX;
            Kenaz.cameraScale.second = scaleX;
        }

        //Display stuff
        map.Show();
        Player->Show();
        Fren->Show();

        Lerp(frenCurrentMoveX, frenCurrentMoveY,
             frenMoveX, frenMoveY, 0.1f);
        Player->Move(playerMoveX, playerMoveY);
        Fren->Move(frenMoveX, frenMoveY);

        std::pair<int, int> middlePoint = MiddlePoint(Player->GetPosition(),
                                                      Fren->GetPosition());

        Kenaz.camera->MoveTo(middlePoint.first,
                             middlePoint.second);
    }

    SDL_Quit();
    return 0;
}