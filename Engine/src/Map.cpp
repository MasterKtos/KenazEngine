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
    for(auto& line : map) {
        for(Texture &tile : line) {
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
    if(index.x >= map.size()-1          || index.x < 0 || map[index.x].empty() ||
       index.y >= map[index.x].size() || index.y < 0)
        return Texture(nullptr, nullptr);
    Texture tile = map[index.x][index.y];
    //tile.Resize({2, 2});
    return tile;
}

std::vector<Vector2> KenazEngine::Map::CheckCollisions(Vector2 position, float radius) {
    // Player position but centered on the nearest tile
    // ------------------------------------------------
    Vector2 posRemainder((int)position.x % tileSize, (int)position.y % tileSize);

    // New concept: player's position is ether between tiles, or perfectly on tile
    // so realistically we need to retrieve just about 4 tiles
    // ---------------------------------------------------------------------------
    //                                            N
    //                                          W   E
    //                                            S
    //
    std::vector<Vector2> tilePositions = {
        {position.x + tileSize - posRemainder.x, position.y - posRemainder.y },            //  NE
        {position.x + tileSize - posRemainder.x, position.y + tileSize - posRemainder.y }, //  SE
        {position.x - posRemainder.x, position.y + tileSize - posRemainder.y },            // WS
        {position.x - posRemainder.x, position.y - posRemainder.y },                       // WN
    };
    std::vector<Vector2> collisions;

    for (auto tilePos : tilePositions) {
        // Player is not "standing" on tile
        // --------------------------------
        //if(position.Distance(tilePos) >= (tileSize/2 + radius/2)*1.41f) continue;

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
