//
// Created by masterktos on 27.12.22.
//

#ifndef KENAZENGINEGAME_MAZE_H
#define KENAZENGINEGAME_MAZE_H

#include "Engine/Map.h"

class Maze : public KenazEngine::Map {
private:
    KenazEngine::Texture targetTile;
    Vector2 target;

public:
    Maze(int tileSize);

    void LoadTile(char tileCode, KenazEngine::Texture *tileLoad) override;
    void LoadMap(const char *filePath) override;

    void Show() override;
    Vector2 GetTarget();
};


#endif //KENAZENGINEGAME_MAZE_H
