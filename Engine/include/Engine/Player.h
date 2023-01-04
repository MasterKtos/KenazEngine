//
// Created by masterktos on 27.12.22.
//

#ifndef KENAZENGINEGAME_PLAYER_H
#define KENAZENGINEGAME_PLAYER_H

#include "Vector2.h"
#include "Texture.h"

namespace KenazEngine {
    class Player {
    private:
        Texture* texture;
        Vector2 currentSpeed;
    public:
        Vector2 speed;
        ///\note
        /// Value range: \<0, 1>  0 - max lerp, 1 - no lerp
        float lerp;

        Player();

        void SetTexture(Texture* newTexture);
        void Show();
        void Move();
        void OnCircleCollide(Vector2 pos);
        void OnBoxCollide(Vector2 pos);

        Vector2 GetPosition();
        float GetSize();
    };
}

#endif //KENAZENGINEGAME_PLAYER_H
