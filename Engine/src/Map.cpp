//
// Created by masterktos on 19.10.22.
//

#include <fstream>
#include "Engine/Map.h"

KenazEngine::Map::Map(int tileSize) : tileSize(tileSize){
}

void KenazEngine::Map::LoadMap(const char* filePath) {
    std::fstream newfile;
    newfile.open(filePath,std::ios::in);
    if (newfile.is_open()) {
        FileToMap(newfile);
        newfile.close();
    }
}

void KenazEngine::Map::FileToMap(std::fstream &mapfile) {
    int lineCount = 1;
    std::string lineString;

    while (getline(mapfile, lineString)) {
        map.emplace_back(std::vector<KenazEngine::Texture>());
        int position = 1;
        for (char znak: lineString) {
            Texture targetTexture(nullptr, nullptr);
            map.back().emplace_back(nullptr, nullptr);
            position++;
            switch (znak) {
                case ' ': continue;
                case '|': targetTexture = wallV; break;
                case '-': targetTexture = wallH; break;
                case '+': targetTexture = wallConnect; break;
                case '.': targetTexture = floor; break;
                default:  position--; continue;
            }
            map.back().back() = targetTexture.GetCopy();
            map.back().back().MoveTo(tileSize * position,
                                     tileSize * lineCount);
        }
        lineCount++;
    }
}

void KenazEngine::Map::Show() {
    for(const auto& line : map) {
        for(auto tile : line) {
            tile.Show();
        }
    }
}

void KenazEngine::Map::Move(int x, int y) {
    for(const auto& line : map) {
        for(Texture tile : line) {
            tile.Move(x, y);
        }
    }
}

// h-horizontal wall, v-vertical wall, c-wall connector, f-floor
void KenazEngine::Map::LoadTile(char tileCode, KenazEngine::Texture *tileLoad) {
    tiles.find(tileCode)->second = tileLoad->GetCopy();
    tiles.find(tileCode)->second.Resize(tileSize, tileSize);
    //return;

    switch(tileCode) {
        case 'h':
            this->wallH = tileLoad->GetCopy();
            wallH.Resize(tileSize, tileSize);
            break;
        case 'v':
            this->wallV = tileLoad->GetCopy();
            wallV.Resize(tileSize, tileSize);
            break;
        case 'c':
            this->wallConnect = tileLoad->GetCopy();
            wallConnect.Resize(tileSize, tileSize);
            break;
        case 'f':
            this->floor = tileLoad->GetCopy();
            floor.Resize(tileSize, tileSize);
            break;
        default:
            return;
    }
}

char KenazEngine::Map::GetTileByPosition(Vector2 position) {
    printf("Position to index mapping: [%d, %d]", (int)position.x/tileSize, (int)position.y/tileSize);
    Texture tile = map[(int)position.x/tileSize][(int)position.y/tileSize];
    if(tile == wallH) return 'h';
    if(tile == wallV) return 'v';
    if(tile == wallConnect) return 'c';
    if(tile == floor) return 'f';
    return 0;
}
