//
// Created by masterktos on 19.10.22.
//

#include <fstream>
#include "Engine/Map.h"

KenazEngine::Map::Map(int tileSize) : tileSize(tileSize){
}

void KenazEngine::Map::LoadMap(const char* filePath) {
    std::string mapString;
    std::string lineString;

    // load file
    std::fstream newfile;
    newfile.open(filePath,std::ios::in);
    if (newfile.is_open()) {
        int lineCount = 1;
        while (getline(newfile, lineString)) {
            map.emplace_back(std::vector<KenazEngine::Texture>());
            int position = 1;
            for (char znak: lineString) {
                Texture targetTexture(nullptr, nullptr);
                position++;
                switch (znak) {
                    case ' ': continue;
                    case '|': targetTexture = wallV; break;
                    case '-': targetTexture = wallH; break;
                    case '+': targetTexture = wallConnect; break;
                    case '.': targetTexture = floor; break;
                    default:  position--; continue;
                }
                map.back().push_back(targetTexture.GetCopy());
                map.back().back().MoveTo(tileSize * position,
                                         tileSize * lineCount);
            }
            lineCount++;
        }
        newfile.close();
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
