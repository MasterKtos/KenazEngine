//
// Created by MasterKtos on 22.11.2022.
//

#include "BallManager.h"

BallManager::BallManager() {

}

void BallManager::ShowBalls() {
    for(Ball ball : balls) ball.Show();
}

void BallManager::CreateBalls(int amount, KenazEngine::Texture &templateTexture) {
    for (int i = 0; i < amount; ++i)
        balls.emplace_back(templateTexture, i);
}

void BallManager::MoveBalls() {
    // Detect collisions
    for(Ball firstBall : balls) {
        for(Ball secondBall : balls) {
            if(firstBall.GetID() == secondBall.GetID()) continue;
            if(firstBall.isColliding(secondBall.GetPosition(), secondBall.GetRadius()))
            {
                float distance = firstBall.GetPosition().Distance(secondBall.GetPosition());
                float overlap = distance - firstBall.GetRadius() - secondBall.GetRadius();
                Vector2 displace, separationVector;
                separationVector.x = (firstBall.GetPosition().x - secondBall.GetPosition().x) / distance;
                separationVector.y = (firstBall.GetPosition().y - secondBall.GetPosition().y) / distance;

                displace.x = overlap * 0.5f * separationVector.x;
                displace.y = overlap * 0.5f * separationVector.y;
                firstBall.SetPosition(firstBall.GetPosition() - displace);
                secondBall.SetPosition(secondBall.GetPosition() + displace);
            }
        }
    }
}
