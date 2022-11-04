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

        Texture wallH = Texture(nullptr);
        Texture wallV = Texture(nullptr);
        Texture wallConnect = Texture(nullptr);
        Texture floor = Texture(nullptr);
    public:
        Map(int tileSize);
        void LoadMap(const char* filePath);
        void LoadTile(char tileCode, Texture* tileLoad);
        void Show();
        void Move(int x, int y);
    };
}

#endif //KENAZENGINEGAME_MAP_H
