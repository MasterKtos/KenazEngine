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

    KenazEngine::Texture* Fren = Kenaz.CreateTexture();
    Fren->Load("guinea_pig.jpg");
    Fren->MoveTo(400, 200);

    //TODO: change the way events are handled
    SDL_Event event;

    int i = 0;
    for (;;i++) {
        Kenaz.UpdateBegin();
        //Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return Kenaz.Quit();
            }
        }

        //Display stuff
        Player->Show();
        Fren->Show();

        //"Animations"
        if(i%200 < 100)
            Player->Move(5, 0);
        else
            Player->Move(-5, 0);
        if(i%400 < 150)
            Fren->Move(-1, 1);
        else if(i%400 < 300)
            Fren->Move(-1, -1);
        else
            Fren->Move(3, 0);
    }


    SDL_Quit();
    return 0;
}
