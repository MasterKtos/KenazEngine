#include <cmath>
#include <iostream>
#include "SDL.h"
#include "Engine/KenazEngine.h"
#include "Engine/Map.h"
#include "Engine/Vector2.h"
#include "Engine/Player.h"
#include "Engine/Overlay.h"
#include "Scripts/Maze.h"
#include "Scripts/Indicator.h"

// Predeclarations
// ---------------
int LoadMapTextures(KenazEngine::KenazEngine Kenaz,
                    KenazEngine::Map &map);

int main(int argc, char *argv[]) {
    Vector2 screenSize(1024, 768);
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

    // Set up players on scene
    // -----------------------
    playerTexture->MoveTo(7*tileSize, -2*tileSize);

    // Add gravity
    // -----------
    //player.speed.y = 9.81f;

    SDL_Event event;

    for (int i=0;;i++) {
        Kenaz.UpdateBegin();

        // Process input
        // -------------
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return Kenaz.Quit();
            }
            if(event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    // player 1
                    case SDLK_UP: player.speed.y = -5; break;
                    case SDLK_DOWN: player.speed.y = 5; break;
                    case SDLK_LEFT: player.speed.x = -5; break;
                    case SDLK_RIGHT: player.speed.x = 5; break;
                }
                //printf("KEYDOWN | %d \n", event.key.keysym.sym);
            }
            if(event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                    //TODO: delet
                    case SDLK_ESCAPE: return Kenaz.Quit(); break;
                        // player 1
                    case SDLK_UP:
                    case SDLK_DOWN: player.speed.y = 0; break;
                    case SDLK_LEFT:
                    case SDLK_RIGHT: player.speed.x = 0; break;
                }
                //printf("KEYUP | %d \n", event.key.keysym.sym);
            }
        }


        // Display stuff
        // -------------
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
        player.Move();


        // Move camera
        // -----------
        auto middlePoint = player.GetPosition();

        Kenaz.camera->MoveTo(middlePoint);
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
