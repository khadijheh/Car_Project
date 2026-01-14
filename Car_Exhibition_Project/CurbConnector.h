#ifndef CURBCONNECTOR_H
#define CURBCONNECTOR_H

#include "Showroom.h"

class CurbConnector {
public:
    // أضف كلمة static هنا
    static void draw(Showroom* s, float centerX, float centerZ, float radius);

private:
    static void drawCurb(Showroom* s, float centerX, float centerZ, float radius);
    static void drawGroundCurve(float centerX, float centerZ, float innerRadius, float outerRadius, float y, float r, float g, float b);
};

#endif