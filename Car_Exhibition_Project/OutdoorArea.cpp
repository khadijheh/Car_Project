#include "OutdoorArea.h"
#include "Showroom.h"
#include <cmath>

OutdoorArea::OutdoorArea(float _x, float _y, float _z, float _w, float _d)
    : x(_x), y(_y), z(_z), width(_w), depth(_d) {
}

void OutdoorArea::draw(Showroom* s, bool isNight) {
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glPushMatrix();
    glTranslatef(x, y, z);
    drawSecurityBollards(s);
  
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, s->asphaltTexture);


    glColor3f(0.3f, 0.3f, 0.3f);

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);

  
    float repeatX = 20.0f;
    float repeatZ = 15.0f;


    glTexCoord2f(0.0f, 0.0f);       glVertex3f(-width / 2.0f, 0.11f, -depth / 2.0f);
    glTexCoord2f(repeatX, 0.0f);    glVertex3f(width / 2.0f, 0.11f, -depth / 2.0f);
    glTexCoord2f(repeatX, repeatZ); glVertex3f(width / 2.0f, 0.11f, depth / 2.0f);
    glTexCoord2f(0.0f, repeatZ);    glVertex3f(-width / 2.0f, 0.11f, depth / 2.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f); 
 
    drawCurb(s);

    drawParkingLines(s);
    drawParkedCars(s);
   
    drawLamps(s, isNight);

    glPopMatrix();
    glEnable(GL_LIGHTING);
    glPopAttrib();
}
void OutdoorArea::drawCurb(Showroom* s) {
    float segmentLen = 5.0f;
    float curbW = 2.0f; 
    float curbH = 1.5f;
    float curveRadius = 12.0f;

    for (float i = -width / 2 + 1; i <= width / 2 - curbW; i += segmentLen) {
        bool isRed = (int((i + width / 2) / segmentLen) % 2 == 0);
        float r = isRed ? 0.8f : 0.9f;
        float g = isRed ? 0.1f : 0.9f;
        float b = isRed ? 0.1f : 0.9f;

        s->drawBox(i + segmentLen / 2, 0.01f, -depth / 2, segmentLen, curbH, curbW, r, g, b, 1.0f);

        if (i < -25.0f || i > 25.0f) {
            s->drawBox(i + segmentLen / 2, 0.01f, depth / 2, segmentLen, curbH, curbW, r, g, b, 1.0f);
        }
    }

    for (float j = -depth / 2; j <= (depth / 2 - curveRadius); j += segmentLen) {
        bool red = (int((j + depth / 2) / segmentLen) % 2 == 0);
        s->drawBox(width / 2, 0.01f, j + segmentLen / 2, 2.0f, 1.2f, segmentLen, (red ? 0.8f : 1.0f), (red ? 0.1f : 1.0f), (red ? 0.1f : 1.0f), 1.0f);
    }
}
void OutdoorArea::drawParkingLines(Showroom* s) {
    float lineW = 0.5f;
    float lineL = 35.0f;
    float spacing = 30.0f;
    float yLine = 0.12f; 
    float yStopper = 0.15f; 
    float safetyMargin = 45.0f;

    for (float j = -depth / 2.0f + safetyMargin; j <= depth / 2.0f - safetyMargin; j += spacing) {
        float rightX = (width / 2.0f) - (lineL / 2.0f) - 4.0f;
        s->drawBox(rightX, yLine, j - 12.0f, lineL, 0.05f, lineW, 1.0f, 1.0f, 1.0f, 0.9f);
        s->drawBox(rightX, yLine, j + 12.0f, lineL, 0.05f, lineW, 1.0f, 1.0f, 1.0f, 0.9f);
        s->drawBox(width / 2.0f - 6.0f, yStopper, j, 2.0f, 0.8f, 10.0f, 1.0f, 0.8f, 0.0f, 1.0f);
    }

    for (float i = -width / 2.0f + safetyMargin; i <= width / 2.0f - safetyMargin; i += spacing) {
        float backZ = -depth / 2.0f + (lineL / 2.0f) + 4.0f;
        s->drawBox(i - 12.0f, yLine, backZ, lineW, 0.05f, lineL, 1.0f, 1.0f, 1.0f, 0.9f);
        s->drawBox(i + 12.0f, yLine, backZ, lineW, 0.05f, lineL, 1.0f, 1.0f, 1.0f, 0.9f);
        s->drawBox(i, yStopper, -depth / 2.0f + 6.0f, 10.0f, 0.8f, 2.0f, 1.0f, 0.8f, 0.0f, 1.0f);

        if (abs(i) > 40.0f) {
            float frontZ = depth / 2.0f - (lineL / 2.0f) - 4.0f;
            s->drawBox(i - 12.0f, yLine, frontZ, lineW, 0.05f, lineL, 1.0f, 1.0f, 1.0f, 0.9f);
            s->drawBox(i + 12.0f, yLine, frontZ, lineW, 0.05f, lineL, 1.0f, 1.0f, 1.0f, 0.9f);
            s->drawBox(i, yStopper, depth / 2.0f - 6.0f, 10.0f, 0.8f, 2.0f, 1.0f, 0.8f, 0.0f, 1.0f);
        }
    }
}
void OutdoorArea::drawLamps(Showroom* s, bool isNight) {
    float lightAlpha = isNight ? 1.0f : 0.2f;
    float yBase = 0.15f;
    int lightCounter = 1;

    auto drawOneLamp = [&](float tx, float tz, float rotY) {
        glPushMatrix();
        glTranslatef(tx, yBase, tz);
        glRotatef(rotY, 0, 1, 0);

        s->drawBox(0, 0, 0, 4.0f, 2.5f, 4.0f, 0.85f, 0.85f, 0.85f, 1.0f);
        s->drawBox(0, 2.5f, 0, 0.8f, 25.0f, 0.8f, 0.1f, 0.1f, 0.1f, 1.0f);
        s->drawBox(1.5f, 26.0f, 0, 5.0f, 0.6f, 1.0f, 0.2f, 0.2f, 0.2f, 1.0f);

        if (isNight) {
            GLfloat emit[] = { 1.0f, 0.9f, 0.5f, 1.0f };
            glMaterialfv(GL_FRONT, GL_EMISSION, emit);
            s->drawBox(4.0f, 25.5f, 0, 2.0f, 0.8f, 1.8f, 1.0f, 0.95f, 0.5f, 1.0f);

            GLfloat no_emit[] = { 0.0f, 0.0f, 0.0f, 1.0f };
            glMaterialfv(GL_FRONT, GL_EMISSION, no_emit);
        }
        else {
            s->drawBox(4.0f, 25.5f, 0, 2.0f, 0.8f, 1.8f, 0.7f, 0.7f, 0.5f, 0.2f);
        }

        GLenum lightID = GL_LIGHT0 + lightCounter;
        if (isNight && lightCounter < 8) {
            GLenum lightID = GL_LIGHT0 + lightCounter;
            glEnable(lightID);

            GLfloat lamp_pos[] = { 4.0f, 25.0f, 0.0f, 1.0f };
            glLightfv(lightID, GL_POSITION, lamp_pos);

            GLfloat spot_dir[] = { 0.0f, -1.0f, 0.0f };
            glLightfv(lightID, GL_SPOT_DIRECTION, spot_dir);

            glLightf(lightID, GL_SPOT_CUTOFF, 60.0f);

            glLightf(lightID, GL_SPOT_EXPONENT, 10.0f);

            GLfloat diffuse[] = { 1.0f, 1.0f, 0.8f, 1.0f };
            glLightfv(lightID, GL_DIFFUSE, diffuse);
            glLightf(lightID, GL_CONSTANT_ATTENUATION, 1.0f);
            glLightf(lightID, GL_LINEAR_ATTENUATION, 0.005f); 
            glLightf(lightID, GL_QUADRATIC_ATTENUATION, 0.0f);

            lightCounter++;
        }
        else {
            glDisable(lightID); 
        }

        glPopMatrix();
        };

    drawOneLamp(width / 2 - 5, -depth / 2 + 10, 135);
    drawOneLamp(width / 2 - 5, 0, 180);
    drawOneLamp(width / 2 - 5, depth / 2 - 10, 225);
    drawOneLamp(0, -depth / 2 + 3, -90);
    drawOneLamp(-40, depth / 2 - 5, 45);
    drawOneLamp(40, depth / 2 - 5, 135);
}
void OutdoorArea::drawSecurityBollards(Showroom* s) {
    float startX = -width / 2.0f + 10.0f;
    float endX = width / 2.0f - 10.0f;
    float zFront = depth / 2.0f + 5.0f;

    for (float i = startX; i <= endX; i += 15.0f) {
        if (abs(i) < 25.0f) continue;

        s->drawBox(i, 0, zFront, 0.8f, 3.5f, 0.8f, 0.9f, 0.9f, 0.9f, 1.0f);
        s->drawBox(i, 2.5f, zFront, 0.9f, 0.5f, 0.9f, 0.8f, 0.0f, 0.0f, 1.0f);
    }
}
void OutdoorArea::drawParkedCars(Showroom* s) {
    float colors[3][3] = {
        {0.67f, 0.67f, 0.67f},
        {0.10f, 0.10f, 0.10f}, 
        {0.85f, 0.85f, 0.85f}  
    };

    float spacing = 30.0f;
    int colorIdx = 0;

    for (float j = -depth / 2.0f + 45.0f; j <= depth / 2.0f - 45.0f; j += spacing) {
        glPushMatrix();

        float rightX = (width / 2.0f) - 25.0f;
        glTranslatef(rightX, 3.5, j);

       
        glRotatef(182.0f, 0.0f, 1.0f, 0.0f);

        glScalef(6.0f, 6.0f, 6.0f);

        glColor3fv(colors[colorIdx % 3]);
        carModel.render();
        glPopMatrix();

        colorIdx++;
    }
}