#include "SDL2/SDL.h"
#include "Engine/KenazEngine.h"

int main(int argc, char *argv[]) {
    KenazEngine::KenazEngine Kenaz;

    Kenaz.SetTitle("SDL Project");
    Kenaz.SetResolution(800, 600);
    Kenaz.SetBackgroundColor(1, 8, 16);

    if (Kenaz.Start()) {
        Kenaz.Update();
    }

    SDL_Quit();
    return 0;
}
