#ifndef WALL_H
#define WALL_H

#include <vector>
#include "Block.h"

class Wall {
public:
    std::vector<Block> blocks;
    int wallTextureID;
    Wall(float startX, float startY, float startZ,
        int width, int height,
        float blockSize,
        float r, float g, float b, int texID);

    void draw();
};

#endif
