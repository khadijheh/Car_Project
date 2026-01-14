#ifndef BLOCK_H
#define BLOCK_H

class Block {
public:
    float x, y, z;
    float size;
    float r, g, b;

    Block(float px, float py, float pz,
        float s,
        float cr, float cg, float cb);

    void draw(int textureID);
};

#endif

