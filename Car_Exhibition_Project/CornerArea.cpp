#include "CornerArea.h"
#include <gl/GL.h>
#include <cmath>

CornerArea::CornerArea(float _x, float _y, float _z, float _radius) {
    x = _x; y = _y; z = _z; radius = _radius;
}

void CornerArea::draw(Showroom* s) {
    glDisable(GL_LIGHTING); 
    int segments = 15;
    for (int i = 0; i <= segments; i++) {
        float angle = i * 90.0f / segments;
        float rad = angle * (3.14159f / 180.0f);

        float posX = x + radius * cos(rad);
        float posZ = z + radius * sin(rad);

        bool isRed = (i % 2 == 0);
        glPushMatrix();
        glTranslatef(posX, 0.5f, posZ); 
        glRotatef(-angle, 0, 1, 0);

        s->drawBox(0, 0, 0, 2.0f, 1.2f, 2.5f, (isRed ? 0.8f : 1.0f), (isRed ? 0.1f : 1.0f), (isRed ? 0.1f : 1.0f), 1.0f);
        glPopMatrix();
    }
    glEnable(GL_LIGHTING); 
}