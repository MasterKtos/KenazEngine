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
int GameLoop(KenazEngine::KenazEngine &Kenaz,
             KenazEngine::Player &player,
             KenazEngine::Player &fren,
             KenazEngine::Map &map,
             Vector2 target,
             std::vector<std::shared_ptr<KenazEngine::Overlay>> countdown,
             const std::shared_ptr<Indicator>& indicatorPlayer,
             const std::shared_ptr<Indicator>& indicatorFren);
int LoadMapTextures(KenazEngine::KenazEngine Kenaz,
                    KenazEngine::Map &map);


int main(int argc, char *argv[]) {
    Vector2 screenSize(1024, 768);
    Vector2 screenCentre(screenSize.x/2, screenSize.y/2);
    int tileSize = 32;
    int gameRounds = 3;

    // Initialize engine parameters
    // ----------------------------
    KenazEngine::KenazEngine Kenaz;
    Kenaz.SetTitle("KenazEngine Game");
    Kenaz.SetResolution(screenSize.x, screenSize.y);
    Kenaz.SetBackgroundColor(1, 8, 16);

    if(!Kenaz.Start()) return 1;

    // Load countdown
    // --------------
    std::vector<std::shared_ptr<KenazEngine::Overlay>> countdown;
    for (int i = 30; i >= 0; --i) {
        std::shared_ptr<KenazEngine::Overlay> currentCountdown = Kenaz.CreateOverlay();
        currentCountdown->Load("countdown/"+std::to_string(i)+".png");
        currentCountdown->Resize(tileSize*2, tileSize*2);
        currentCountdown->MoveTo(screenCentre.x, screenSize.y-tileSize*2);
        countdown.push_back(currentCountdown);
    }

    // Load textures
    // -------------
    KenazEngine::Texture* targetTexture = Kenaz.CreateTexture();
    targetTexture->Load("circle.png");

    KenazEngine::Texture* playerTexture = Kenaz.CreateTexture();
    playerTexture->Load("square.png");
    playerTexture->Resize(tileSize, tileSize);
    playerTexture->MoveTo(400, 300);

    KenazEngine::Texture* frenTexture = Kenaz.CreateTexture();
    frenTexture->Load("circle.png");
    frenTexture->Resize(tileSize, tileSize);
    frenTexture->MoveTo(500, 400);

    // Set up players
    // --------------
    KenazEngine::Player player, fren;
    player.SetTexture(playerTexture);
    player.lerp = 0.2f;
    fren.SetTexture(frenTexture);
    fren.lerp = 0.2f;

    std::shared_ptr<Indicator> indicatorPlayer = Kenaz.CreateIndicator();
    indicatorPlayer->Load("indicator-blue.png");
    indicatorPlayer->MoveTo(player.GetPosition());
    std::shared_ptr<Indicator> indicatorFren = Kenaz.CreateIndicator();
    indicatorFren->Load("indicator-orange.png");
    indicatorFren->MoveTo(fren.GetPosition());

    // Load map
    // --------
    Maze map(tileSize);
    LoadMapTextures(Kenaz, map);
    map.LoadTile('t', targetTexture);

    int i = 1, score = 0;
    do {
        map.LoadMap(std::string ("../../map"+std::to_string(i)+".txt").c_str());
        score += GameLoop(Kenaz, player, fren,
                          map, map.GetTarget(), countdown,
                          indicatorPlayer, indicatorFren);

        // Reset players
        // -------------
        playerTexture->MoveTo(400, 300);
        frenTexture->MoveTo(500, 400);
        indicatorPlayer->MoveTo(player.GetPosition());
        indicatorFren->MoveTo(fren.GetPosition());
        i++;
    } while(i <= gameRounds);

    printf("=== Your score: %d ===", score);

    SDL_Quit();
    return 0;

}

int GameLoop(KenazEngine::KenazEngine &Kenaz,
             KenazEngine::Player &player,
             KenazEngine::Player &fren,
             KenazEngine::Map &map,
             Vector2 target,
             std::vector<std::shared_ptr<KenazEngine::Overlay>> countdown,
             const std::shared_ptr<Indicator>& indicatorPlayer,
             const std::shared_ptr<Indicator>& indicatorFren) {
    SDL_Event event;
    int startTicks = SDL_GetTicks();
    indicatorPlayer->target = target;
    indicatorFren->target = target;

    for (int i=0;;i++) {
        Kenaz.UpdateBegin();

        int currentTime = (SDL_GetTicks()-startTicks)/1000;
        if(currentTime >= countdown.size()) return 0;

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
                switch(event.key.keysym.sym) {
                    // player 2
                    case SDLK_w: fren.speed.y = -5; break;
                    case SDLK_s: fren.speed.y = 5; break;
                    case SDLK_a: fren.speed.x = -5; break;
                    case SDLK_d: fren.speed.x = 5; break;
                }
                //printf("KEYDOWN | %d \n", event.key.keysym.sym);
            }
            if(event.type == SDL_KEYUP) {
                switch(event.key.keysym.sym) {
                    //TODO: delet
                    case SDLK_DELETE: return 1; break;
                    case SDLK_ESCAPE: return Kenaz.Quit(); break;
                    // player 1
                    case SDLK_UP:
                    case SDLK_DOWN: player.speed.y = 0; break;
                    case SDLK_LEFT:
                    case SDLK_RIGHT: player.speed.x = 0; break;
                }
                switch(event.key.keysym.sym) {
                    // player 2
                    case SDLK_w:
                    case SDLK_s: fren.speed.y = 0; break;
                    case SDLK_a:
                    case SDLK_d: fren.speed.x = 0; break;
                }
                //printf("KEYUP | %d \n", event.key.keysym.sym);
            }
        }


        // Display stuff
        // -------------
        map.Show();
        player.Show();
        fren.Show();
        countdown[currentTime]->Show();
        indicatorPlayer->Show();
        indicatorFren->Show();


        // Apply movement
        // --------------
        player.Move();
        fren.Move();

        indicatorPlayer->MoveTo(player.GetPosition());
        indicatorFren->MoveTo(fren.GetPosition());

        // Check collisions
        // ----------------
        for(auto collision : map.CheckCollisions(player.GetPosition())) {
            player.OnBoxCollide(collision);
        }

        for(auto collision : map.CheckCollisions(fren.GetPosition())) {
            fren.OnCircleCollide(collision);
        }

        // Move camera
        // -----------
        auto middlePoint = Vector2::MiddlePoint(player.GetPosition(),
                                                      fren.GetPosition());

        Kenaz.camera->MoveTo(middlePoint);

        // Check if target was reached
        // ---------------------------
        if(player.GetPosition().Distance(target) < 10 ||
           fren.GetPosition().Distance(target) < 10)
            return 1;
    }
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
