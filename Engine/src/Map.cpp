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
    map.clear();
    int lineCount = 1;
    std::string lineString;

    while (getline(mapfile, lineString)) {
        map.emplace_back();
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
            if(tile.isValid()) tile.Show();
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

KenazEngine::Texture KenazEngine::Map::GetTileByPosition(Vector2 position) {
    //printf("Position to index mapping: [%d, %d]; Player position: %s",
    //       (int)position.x/tileSize, (int)position.y/tileSize, position.toString().c_str());
    Vector2 index((int)position.y/tileSize - 1, (int)position.x/tileSize - 2);
    if(index.x >= map.size()) return Texture(nullptr, nullptr);
    if(index.y >= map[index.y].size()) return Texture(nullptr, nullptr);
    Texture tile = map[index.x][index.y];
    //tile.Resize({2, 2});
    return tile;
}

std::vector<Vector2> KenazEngine::Map::CheckCollisions(Vector2 position, float radius) {
    // Player position but centered on the nearest tile
    // ------------------------------------------------
    Vector2 remainder((int)position.x%tileSize, (int)position.y%tileSize);
    Vector2 nPosition = {
            remainder.x>=tileSize/2 ? position.x + (tileSize - remainder.x) : position.x - remainder.x,
            remainder.y>=tileSize/2 ? position.y + (tileSize - remainder.y) : position.y - remainder.y
    };
    //printf("[[ remainder: %s || normalized pos: %s ]]",
    //       remainder.toString().c_str(), nPosition.toString().c_str());

    // Tiles around player
    // -------------------
    //                                N
    //                              W   E
    //                                s
    std::vector<Vector2> tilePositions = {
            { nPosition.x, nPosition.y - tileSize },              //  N
            { nPosition.x + tileSize, nPosition.y - tileSize },   //  NE
            { nPosition.x + tileSize, nPosition.y },              //   E
            { nPosition.x + tileSize, nPosition.y + tileSize },   //  SE
            { nPosition.x, nPosition.y + tileSize },              //  S
            { nPosition.x - tileSize, nPosition.y + tileSize },   // WS
            { nPosition.x - tileSize, nPosition.y },              // W
            { nPosition.x - tileSize, nPosition.y - tileSize }    // WN
    };
    std::vector<Vector2> collisions;

    for (auto tilePos : tilePositions) {
        // Player is not "standing" on tile
        // --------------------------------
        if(position.Distance(tilePos) >= (tileSize/2 + radius/2)*1.1f) continue;

        // Get tile at position and check if it's not empty
        // ------------------------------------------------
        auto tile = GetTileByPosition(tilePos);
        if(!tile.isValid()) continue;

        // Player collides if tile is a wall
        // ---------------------------------
        if(tile == wallH || tile == wallV || tile == wallConnect)
            collisions.push_back(tilePos);
    }

    return collisions;
}
