#include "Wall.h"

Wall::Wall(float startX, float startY, float startZ,
    int width, int height,
    float blockSize,
    float r, float g, float b, int texID)
{
    this->wallTextureID = texID;
    float gap = 0.005f; 
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            float x = startX + i * (blockSize + gap);
            float y = startY + j * (blockSize + gap);
            float z = startZ;
            blocks.emplace_back(x, y, z, blockSize, r, g, b);
        }
    }
}


void Wall::draw() 
{
    for (auto& block : blocks) {
        block.draw(this->wallTextureID); 
    }
}