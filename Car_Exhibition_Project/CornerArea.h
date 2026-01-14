#include "Showroom.h"
class CornerArea {
public:
    float x, y, z, radius;
    CornerArea(float _x, float _y, float _z, float _r);
    void draw(Showroom* s);
};