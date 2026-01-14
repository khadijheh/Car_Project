#include "FrontArea.h"
#include <GL/gl.h>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "CurbConnector.h"

FrontArea::FrontArea(float _x, float _y, float _z, float _w, float _d)
    : x(_x), y(_y), z(_z), width(_w), depth(_d) {
}

void FrontArea::draw(Showroom* s, bool isNight) {
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
   glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glPushMatrix();
    glTranslatef(x, y, z);

    drawAsphalt(s);

    drawMainCurb(s);

    drawParkingSlots(s);


 
    glPopMatrix();
}

void FrontArea::drawAsphalt(Showroom* s) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, s-> asphaltTexture);

    glColor3f(0.3f, 0.3f, 0.3f);

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-(width / 2.0f), 0.11f, 0.0f);
    glTexCoord2f(15.0f, 0.0f);  glVertex3f((width / 2.0f) + 126.0f, 0.11f, 0.0f);
    glTexCoord2f(15.0f, 10.0f); glVertex3f((width / 2.0f) + 126.0f, 0.11f, depth);
    glTexCoord2f(0.0f, 10.0f);  glVertex3f(-(width / 2.0f), 0.11f, depth);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
}
void FrontArea::drawMainCurb(Showroom* s) {
    float segmentLen = 6.0f;
    float curbW = 2.5f;
    float curbH = 1.2f;
    float curveRadius = 12.0f; 

    for (float i = -width / 2.0f; i <= (width / 2.0f - curveRadius); i += segmentLen) {
        bool isRed = (int((i + width / 2.0f) / segmentLen) % 2 == 0);
        float r = isRed ? 0.8f : 1.0f;
        float g = isRed ? 0.1f : 1.0f;
        float b = isRed ? 0.1f : 1.0f;

        s->drawBox(i + segmentLen / 2.0f, 0.05f, depth, segmentLen, curbH, curbW, r, g, b, 1.0f);
    }

   
}
void FrontArea::drawParkingSlots(Showroom* s) {
    float lineW = 0.5f;
    float lineL = 35.0f; 
    float spacing = 30.0f;
    float yLine = 0.12f;
    float yStopper = 0.15f;

    for (float i = -width / 2.0f + 40.0f; i <= width / 2.0f - 40.0f; i += spacing) {
        if (abs(i) < 30.0f) continue;

        float frontZ = depth - (lineL / 2.0f) - 4.0f;

        s->drawBox(i - 12.0f, yLine, frontZ, lineW, 0.05f, lineL, 1.0f, 1.0f, 1.0f, 0.9f);
        s->drawBox(i + 12.0f, yLine, frontZ, lineW, 0.05f, lineL, 1.0f, 1.0f, 1.0f, 0.9f);

        s->drawBox(i, yStopper, depth - 6.0f, 10.0f, 0.8f, 2.0f, 1.0f, 0.8f, 0.0f, 1.0f);
    }
}
void FrontArea::drawGreenBelts(Showroom* s) {
    float grassW = 15.0f;
    s->drawBox(-width / 2.0f - grassW / 2.0f, 0.05f, depth / 2.0f, grassW, 0.2f, depth, 0.2f, 0.5f, 0.2f, 1.0f);
    s->drawBox(width / 2.0f + grassW / 2.0f, 0.05f, depth / 2.0f, grassW, 0.2f, depth, 0.2f, 0.5f, 0.2f, 1.0f);
}
void FrontArea::drawCurbCurve(Showroom* s, float centerX, float centerZ, float radius) {
    float curbW = 2.5f;
    float curbH = 1.2f;
    float arcSegmentLen = 1.8f; 
    int numSegments = 16;    

    for (int i = 0; i <= numSegments; i++) {
        float angle = (i * 90.0f / numSegments) * (M_PI / 180.0f);

        float posX = centerX + radius * cos(angle);
        float posZ = centerZ + radius * sin(angle);

        bool isRed = (i % 2 == 0);
        float r = isRed ? 0.8f : 1.0f;
        float g = isRed ? 0.1f : 1.0f;
        float b = isRed ? 0.1f : 1.0f;

        glPushMatrix();
        glTranslatef(posX, 0.07f, posZ);

        glRotatef(-(i * 90.0f / numSegments), 0, 1, 0);

        s->drawBox(0, 0, 0, arcSegmentLen, curbH, curbW, r, g, b, 1.0f);
        glPopMatrix();
    }
}
void FrontArea::drawAsphaltCurve(Showroom* s, float centerX, float centerZ, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.12f, 0.12f, 0.14f); 
    glVertex3f(centerX, 0.01f, centerZ); 

    int segments = 20;
    for (int i = 0; i <= segments; i++) {
        float angle = (i * 90.0f / segments) * (M_PI / 180.0f);
        float px = centerX + radius * cos(angle);
        float pz = centerZ + radius * sin(angle);
        glVertex3f(px, 0.01f, pz);
    }
    glEnd();
}