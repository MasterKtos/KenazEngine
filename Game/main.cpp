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
    Player->Load("Player.jpg");
    Player->MoveTo(20, 50);

    //TODO: change the way events are handled
    SDL_Event event;

    for (;;) {
        Kenaz.UpdateBegin();
        //Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return Kenaz.Quit();
            }
        }

        //Display stuff
        Player->Show();
        Player->Move(5, 0);
    }


    SDL_Quit();
    return 0;
}
