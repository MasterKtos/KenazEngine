//
// Created by masterktos on 19.10.22.
//

#ifndef KENAZENGINEGAME_MAP_H
#define KENAZENGINEGAME_MAP_H

#include <vector>
#include <unordered_map>
#include "Texture.h"

namespace KenazEngine {

    class Map {
    protected:
        std::vector<std::vector<Texture>> map;
        int tileSize;

        Texture wallH = Texture(nullptr, nullptr);
        Texture wallV = Texture(nullptr, nullptr);
        Texture wallConnect = Texture(nullptr, nullptr);
        Texture floor = Texture(nullptr, nullptr);

        std::unordered_map<char, Texture> tiles {
            {'h', Texture(nullptr, nullptr)},
            {'v', Texture(nullptr, nullptr)},
            {'c', Texture(nullptr, nullptr)},
            {'f', Texture(nullptr, nullptr)}
        };


        void FileToMap(std::fstream &mapfile);
    public:
        Map(int tileSize);

        virtual void LoadMap(const char* filePath);
        virtual void LoadTile(char tileCode, Texture* tileLoad);

        virtual void Show();
        void Move(int x, int y);
        char GetTileByPosition(Vector2 position);
    };
}

#endif //KENAZENGINEGAME_MAP_H
