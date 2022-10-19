//
// Created by masterktos on 19.10.22.
//

#ifndef KENAZENGINEGAME_MAP_H
#define KENAZENGINEGAME_MAP_H

#include <vector>
#include "Texture.h"

namespace KenazEngine {

    class Map {
    private:
        std::vector<std::vector<Texture>> map;
        int tileSize;

        Texture wall = Texture(nullptr);
        Texture floor = Texture(nullptr);
    public:
        Map(int tileSize);
        void LoadMap(const char* filePath);
        void LoadFloor(Texture* floorLoad);
        void LoadWall(Texture* wallLoad);
        void Show();
    };
}

#endif //KENAZENGINEGAME_MAP_H
