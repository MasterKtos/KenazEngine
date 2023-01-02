//
// Created by masterktos on 27.12.22.
//

#include <fstream>
#include <sstream>
#include "Maze.h"

Maze::Maze(int tileSize) :
        Map(tileSize),
        targetTile(nullptr, nullptr) {
    tiles.insert({'t', KenazEngine::Texture(nullptr, nullptr)});
}

void Maze::LoadMap(const char *filePath) {
    std::fstream newfile;
    std::string fileTargetPos;
    newfile.open(filePath,std::ios::in);
    if (newfile.is_open()) {
        // Load target position
        // --------------------
        getline(newfile, fileTargetPos);
        std::stringstream targetPos(fileTargetPos);
        targetPos >> target.x >> target.y;
        targetTile.MoveTo(target);

        FileToMap(newfile);
        newfile.close();
    }
}

void Maze::LoadTile(char tileCode, KenazEngine::Texture *tileLoad) {
    Map::LoadTile(tileCode, tileLoad);
    if(tileCode == 't') {
        this->targetTile = tileLoad->GetCopy();
        targetTile.Resize(tileSize, tileSize);
    }
}

void Maze::Show() {
    Map::Show();
    targetTile.Show();
}

Vector2 Maze::GetTarget() {
    return Vector2(target.x, target.y);
}
