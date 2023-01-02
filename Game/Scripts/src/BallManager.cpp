//
// Created by MasterKtos on 22.11.2022.
//

#include "../BallManager.h"

BallManager::BallManager() : reflectionEnabled(true), separationEnabled(true) {
}

void BallManager::ShowBalls() {
    for(Ball ball : balls) ball.Show();
}

void BallManager::CreateBalls(int amount, KenazEngine::Texture &templateTexture) {
    for (int i = 0; i < amount; ++i)
        balls.emplace_back(templateTexture, i);
}

void BallManager::RandomizeBalls() {
    srand(time(nullptr));
    for(Ball &ball : balls) {
        ball.SetPosition(rand() % 800 + 1, rand() % 600 + 1);
        float radius = rand() % 5 + 15;
        ball.SetSpeed((20 - radius) * (rand()%2 == 1? -1:1),
                      (20 - radius) * (rand()%2 == 1? -1:1));
        ball.SetRadius(radius);
    }
}

void BallManager::MoveBalls() {
    for(Ball &firstBall : balls) {
        for(Ball &secondBall : balls) {
            // Detect collisions with other balls
            if(firstBall.GetID() == secondBall.GetID()) continue;
            if(firstBall.isColliding(secondBall.GetPosition(), secondBall.GetRadius()))
            {
                firstBall.OnCollide(secondBall.GetPosition(), secondBall.GetRadius(), reflectionEnabled, separationEnabled);
                secondBall.OnCollide(firstBall.GetPosition(), firstBall.GetRadius(), reflectionEnabled, separationEnabled);
            }
        }
        // Detect collisions with boundaries
        firstBall.CheckBounds(800, 600);

        firstBall.Move();
    }
}
