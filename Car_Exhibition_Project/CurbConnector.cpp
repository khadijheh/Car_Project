#include "CurbConnector.h"
#include <gl/gl.h>
#include <cmath>

#ifndef DEG2RAD
#define DEG2RAD 0.0174532925f
#endif

void CurbConnector::draw(Showroom* s, float centerX, float centerZ, float radius) {
 
    drawCurb(s, centerX, centerZ, radius);
}
void CurbConnector::drawCurb(Showroom* s, float centerX, float centerZ, float radius) {
    float curbWidth = 2.5f;
    float curbHeight = 1.2f;
    float arcSegmentLen = 1.0f;
    int segments = 40; 

    for (int i = 0; i <= segments; i++) {
        float angleDeg = 90.0f - (i * 90.0f / segments);
        float rad = angleDeg * (3.14159f / 180.0f);

        float posX = centerX + radius * cos(rad);
        float posZ = centerZ + radius * sin(rad);

        glPushMatrix();
        glTranslatef(posX, 0.06f, posZ);

        glRotatef(90.0f - angleDeg, 0, 1, 0);

        bool isRed = ((i / 4) % 2 != 0); 
        float r = isRed ? 0.8f : 1.0f;
        float g = isRed ? 0.1f : 1.0f;
        float b = isRed ? 0.1f : 1.0f;

        s->drawBox(0, 0, 0, 0.5f, curbHeight, curbWidth, r, g, b, 1.0f);

        glPopMatrix();
    }
}