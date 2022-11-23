//
// Created by MasterKtos on 22.11.2022.
//

#ifndef KENAZENGINEGAME_BALLMANAGER_H
#define KENAZENGINEGAME_BALLMANAGER_H


#include <vector>
#include "Ball.h"

class BallManager {
private:
    std::vector<Ball> balls;

public:
    BallManager();

    void ShowBalls();

    void CreateBalls(int amount, KenazEngine::Texture &templateTexture);
    void MoveBalls();
};


#endif //KENAZENGINEGAME_BALLMANAGER_H
