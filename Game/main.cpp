#include <cmath>
#include <iostream>
#include "SDL.h"
#include "Engine/KenazEngine.h"

float vectorLength(float x, float y) {
    return std::sqrt(x*x + y*y);
}

bool collided(float pos1[2], float pos2[2], float radius) {
    float x = pos1[0]-pos2[0];
    float y = pos1[1]-pos2[1];
    return abs(x*x + y*y) <= radius*2*radius*2 + 0.5f;
}

int main(int argc, char *argv[]) {
    std::pair<int, int> screenSize = {800, 600};

    KenazEngine::KenazEngine Kenaz;

    // Initialize engine parameters
    Kenaz.SetTitle("SDL Project");
    Kenaz.SetResolution(screenSize.first, screenSize.second);
    Kenaz.SetBackgroundColor(1, 8, 16);

    if(!Kenaz.Start()) return 1;

    KenazEngine::Texture* Fren = Kenaz.CreateTexture();
    Fren->Load("circle.png");
    Fren->Resize(32, 32);
    Fren->MoveTo(500, 400);

    float frenMoveX = 0;
    float frenMoveY = 0;
    float frenPos[2] = {500, 400};

    float moveVectorX = -5;
    float moveVectorY = 0;

    KenazEngine::Texture* Fren2 = Kenaz.CreateTexture();
    Fren2->Load("circle.png");
    Fren2->Resize(32, 32);
    Fren2->MoveTo(100, 400);

    float fren2MoveX = 0;
    float fren2MoveY = 0;
    float fren2Pos[2] = {100, 400};
    float radius = 16;

    float moveVector2X = 5;
    float moveVector2Y = 0;

    SDL_Event event;

    for (int i=0;;i++) {
        Kenaz.UpdateBegin();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return Kenaz.Quit();
            }
        }

        Fren->Show();
        Fren2->Show();

        if(collided(frenPos, fren2Pos, radius))
        {
            printf("e\n");
            moveVectorX = -moveVectorX;
            moveVectorY = -moveVectorY;

            moveVector2X = -moveVector2X;
            moveVector2Y = -moveVector2Y;
        }

        frenMoveX = moveVectorX;
        frenMoveY = moveVectorY;

        frenPos[0] += frenMoveX;
        frenPos[1] += frenMoveY;

        if(frenPos[0] <= 0 || frenPos[0] >= screenSize.first)
        {
            moveVectorX = -moveVectorX;
            frenMoveX = moveVectorX*2;
            frenPos[0] += frenMoveX;
        }
        if(frenPos[1] <= 0 || frenPos[1] >= screenSize.second)
        {
            moveVectorY = -moveVectorY;
            frenMoveY = moveVectorY*2;
            frenPos[1] += frenMoveY;
        }

        fren2MoveX = moveVector2X;
        fren2MoveY = moveVector2Y;

        fren2Pos[0] += fren2MoveX;
        fren2Pos[1] += fren2MoveY;

        if(fren2Pos[0] <= 0 || fren2Pos[0] >= screenSize.first)
        {
            moveVector2X = -moveVector2X;
            fren2MoveX = moveVector2X*2;
            fren2Pos[0] += fren2MoveX;
        }
        if(fren2Pos[1] <= 0 || fren2Pos[1] >= screenSize.second)
        {
            moveVector2Y = -moveVector2Y;
            fren2MoveY = moveVector2Y*2;
            fren2Pos[1] += fren2MoveY;
        }

        Fren->Move(frenMoveX, frenMoveY);
        Fren2->Move(fren2MoveX, fren2MoveY);
    }
}