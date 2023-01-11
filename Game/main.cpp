#include <iostream>
#include <chrono>
#include "SDL.h"
#include "Engine/KenazEngine.h"
#include "Engine/Map.h"
#include "Engine/Vector2.h"
#include "Engine/Player.h"

// Predeclarations
// ---------------
int LoadMapTextures(KenazEngine::KenazEngine Kenaz,
                    KenazEngine::Map &map);

int main(int argc, char *argv[]) {
    Vector2 screenSize(1366, 768);
    Vector2 screenCentre(screenSize.x/2, screenSize.y/2);
    int tileSize = 32;

    // Initialize engine parameters
    // ----------------------------
    KenazEngine::KenazEngine Kenaz;
    Kenaz.SetTitle("KenazEngine Game");
    Kenaz.SetResolution(screenSize.x, screenSize.y);
    Kenaz.SetBackgroundColor(1, 8, 16);

    if(!Kenaz.Start()) return 1;

    // Load textures
    // -------------
    KenazEngine::Texture* playerTexture = Kenaz.CreateTexture();
    playerTexture->Load("square.png");
    playerTexture->Resize(tileSize/4 * 3, tileSize/4 * 3);

    KenazEngine::Texture* frenTexture = Kenaz.CreateTexture();
    frenTexture->Load("circle.png");
    frenTexture->Resize(tileSize/4 * 3, tileSize/4 * 3);

    // Set up players
    // --------------
    KenazEngine::Player player;
    player.SetTexture(playerTexture);
    player.speedLerp = 0.2f;

    // Load map
    // --------
    KenazEngine::Map map(tileSize);
    LoadMapTextures(Kenaz, map);
    map.LoadMap(std::string ("../../platformer.txt").c_str());

    // Load background maps
    // --------------------
    KenazEngine::Texture *Cloud = Kenaz.CreateTexture();
    Cloud->Load("layers/cloud.png");
    KenazEngine::Texture *Wall = Kenaz.CreateTexture();
    Wall->Load("layers/wall.png");
    KenazEngine::Texture *Sky = Kenaz.CreateTexture();
    Sky->Load("layers/sky.png");
    KenazEngine::Texture *SkyGradient = Kenaz.CreateTexture();
    SkyGradient->Load("layers/skyGradient.png");
    KenazEngine::Texture *SkyDark = Kenaz.CreateTexture();
    SkyDark->Load("layers/skyDark.png");
    KenazEngine::Texture *Dirt = Kenaz.CreateTexture();
    Dirt->Load("layers/dirt.png");
    KenazEngine::Texture *DirtUp = Kenaz.CreateTexture();
    DirtUp->Load("layers/dirtUp.png");

    KenazEngine::Map mapBG1(tileSize);
    {
        mapBG1.LoadTile('v', Wall);
        mapBG1.LoadMap(std::string("../../platformer_bg1.txt").c_str());
    }
    KenazEngine::Map mapBG2(tileSize);
    {
        mapBG2.LoadTile('h', DirtUp);
        mapBG2.LoadTile('f', Dirt);
        mapBG2.LoadMap(std::string("../../platformer_bg2.txt").c_str());
    }
    KenazEngine::Map mapBG3(tileSize);
    {
        mapBG3.LoadTile('f', Sky);
        mapBG3.LoadTile('c', SkyGradient);
        mapBG3.LoadTile('v', SkyDark);
        mapBG3.LoadTile('h', Cloud);
        mapBG3.LoadMap(std::string("../../platformer_bg3.txt").c_str());
    }

    // Set up players on scene
    // -----------------------
    playerTexture->MoveTo(15*tileSize, 35*tileSize);

    // Add gravity
    // -----------
    //player.speed.y = 9.81f;

    SDL_Event event;

    auto StartTime = std::chrono::high_resolution_clock::now();
    auto FrameEndTime = StartTime;
    std::chrono::duration<double> DeltaTime{};

    int div1 = 1;
    int div2 = 1;
    int div3 = 1;




    for (int i=0;;i++) {
        Kenaz.UpdateBegin(DeltaTime.count());

        // Process input
        // -------------
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return Kenaz.Quit();
            }
            if(event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    // Player 1
                    // --------
                    // Speed
                    //case SDLK_UP: player.speed.y = -5; break;
                    //case SDLK_DOWN: player.speed.y = 5; break;
                    case SDLK_LEFT: player.speed.x = -5; break;
                    case SDLK_RIGHT: player.speed.x = 5; break;
                        // Functions
                    case /*SPACE*/32: player.Jump(); break;

                    // Other
                    // -----
                    case SDLK_ESCAPE: return Kenaz.Quit(); break;
                }
                //printf("KEYDOWN | ]%d[ \n", event.key.keysym.sym);
            }
            if(event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                    // Player 1
                    // --------
                    // Speed
                    //case SDLK_UP:
                    //case SDLK_DOWN: player.speed.y = 0; break;
                    case SDLK_LEFT:
                    case SDLK_RIGHT: player.speed.x = 0; break;

                    case SDLK_u: div1--; printf("DIV1: %d\n", div1); break;
                    case SDLK_i: div1++; printf("DIV1: %d\n", div1); break;
                    case SDLK_j: div2--; printf("DIV2: %d\n", div2); break;
                    case SDLK_k: div2++; printf("DIV2: %d\n", div2); break;
                    case SDLK_n: div3--; printf("DIV3: %d\n", div3); break;
                    case SDLK_m: div3++; printf("DIV3: %d\n", div3); break;
                }
                //printf("KEYUP | %d \n", event.key.keysym.sym);
            }
        }


        // Display stuff
        // -------------
        mapBG3.Show();
        mapBG2.Show();
        mapBG1.Show();
        map.Show();
        player.Show();

        // Check collisions
        // ----------------
        auto collisions = map.CheckCollisions(player.GetPosition(), player.GetSize());
        player.AnalyzeCollisions(collisions, tileSize/2);
        // Clear collision vector if there are no collisions
        //if(collisions.empty()) player.OnBoxCollide(Vector2(0, 0), tileSize/2);

        // Apply movement
        // --------------
        player.Move(DeltaTime.count());


        // Move camera
        // -----------
        auto middlePoint = Vector2::Lerp(Kenaz.camera->Position, player.GetPosition(), 0.9f);

            // Apply parallax effect
            // ---------------------
            auto posDelta = player.posDelta;
//            printf("Delta:\t\t\t%s\n", posDelta.toStringf().c_str());



            mapBG1.Move(posDelta.x/div1, -posDelta.y/div1);
            mapBG2.Move(posDelta.x/div2, -posDelta.y/div2);
            mapBG3.Move(posDelta.x/div3, -posDelta.y/div3);

        Kenaz.camera->MoveTo(middlePoint);

        //Calculate timers
        DeltaTime = std::chrono::high_resolution_clock::now() - FrameEndTime;
        FrameEndTime = std::chrono::high_resolution_clock::now();
    }

    SDL_Quit();
    return 0;

}

int LoadMapTextures(KenazEngine::KenazEngine Kenaz, KenazEngine::Map &map) {
    KenazEngine::Texture* Floor = Kenaz.CreateTexture();
    Floor->Load("floor.png");

    KenazEngine::Texture* WallH = Kenaz.CreateTexture();
    WallH->Load("wall_horizontal.png");

    KenazEngine::Texture* WallV = Kenaz.CreateTexture();
    WallV->Load("wall_vertical.png");

    KenazEngine::Texture* WallC = Kenaz.CreateTexture();
    WallC->Load("wall_connector.png");

    map.LoadTile('f', Floor);
    map.LoadTile('h', WallH);
    map.LoadTile('v', WallV);
    map.LoadTile('c', WallC);
}
