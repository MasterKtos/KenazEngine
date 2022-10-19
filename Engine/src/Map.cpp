//
// Created by masterktos on 19.10.22.
//

#include <fstream>
#include "Engine/Map.h"



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
                switch (znak) {
                    case ' ':
                        position++;
                        break;
                    case '|':
                    case '-':
                        map.back().push_back(wall.GetCopy());
                        map.back().back().MoveTo(tileSize * position,
                                                 tileSize * lineCount);
                        position++;
                        break;
                    case '.':
                        map.back().push_back(floor.GetCopy());
                        map.back().back().MoveTo(tileSize * position,
                                                 tileSize * lineCount);
                        position++;
                        break;
                    default:
                        break;
                }
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

void KenazEngine::Map::LoadFloor(KenazEngine::Texture *floorLoad) {
    this->floor = floorLoad->GetCopy();
    floor.Resize(tileSize, tileSize);
}

void KenazEngine::Map::LoadWall(KenazEngine::Texture *wallLoad) {
    this->wall = wallLoad->GetCopy();
    floor.Resize(tileSize, tileSize);
}

KenazEngine::Map::Map(int tileSize) : tileSize(tileSize){
}
