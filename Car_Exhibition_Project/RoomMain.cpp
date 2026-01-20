#include "RoomMain.h"

RoomMain::RoomMain(GLuint f, GLuint w, GLuint c)
    : floorTex(f), wallTex(w), ceilTex(c) {
    size = 25.0f;
    height = 15.0f;
    doorWidth = 15.0f;
    doorHeight = 11.0f;
    doorAngle = 0.0f;
}

void RoomMain::drawBaseStructure() {
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, floorTex);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, 0.0f, size);
    glTexCoord2f(5.0f, 0.0f); glVertex3f(size, 0.0f, size);
    glTexCoord2f(5.0f, 5.0f); glVertex3f(size, 0.0f, -size);
    glTexCoord2f(0.0f, 5.0f); glVertex3f(-size, 0.0f, -size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    glColor4f(0.5f, 0.7f, 1.0f, 0.3f); 
    glBegin(GL_QUADS);
    glVertex3f(-size, 0, -size); glVertex3f(size, 0, -size);
    glVertex3f(size, height, -size); glVertex3f(-size, height, -size);
    glVertex3f(-size, 0, size); glVertex3f(-size, 0, -size);
    glVertex3f(-size, height, -size); glVertex3f(-size, height, size);
    glVertex3f(size, 0, -size); glVertex3f(size, 0, size);
    glVertex3f(size, height, size); glVertex3f(size, height, -size);
    glEnd();

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glEnable(GL_TEXTURE_2D); 
    glBindTexture(GL_TEXTURE_2D, ceilTex);
    glColor3f(1.0f, 1.0f, 1.0f); 

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-size, height, size);
    glTexCoord2f(1, 0); glVertex3f(size, height, size);
    glTexCoord2f(1, 1); glVertex3f(size, height, -size);
    glTexCoord2f(0, 1); glVertex3f(-size, height, -size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
void RoomMain::drawFrontGlassWall() {
    glColor3f(0.4f, 0.2f, 0.0f); 

    glBegin(GL_QUADS);
    glVertex3f(-size, doorHeight - 0.5f, size + 0.02f);
    glVertex3f(size, doorHeight - 0.5f, size + 0.02f);
    glVertex3f(size, doorHeight + 0.5f, size + 0.02f);
    glVertex3f(-size, doorHeight + 0.5f, size + 0.02f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-size, 0, size + 0.02f); glVertex3f(-size + 0.5f, 0, size + 0.02f);
    glVertex3f(-size + 0.5f, height, size + 0.02f); glVertex3f(-size, height, size + 0.02f);

    glVertex3f(size - 0.5f, 0, size + 0.02f); glVertex3f(size, 0, size + 0.02f);
    glVertex3f(size, height, size + 0.02f); glVertex3f(size - 0.5f, height, size + 0.02f);
    glEnd();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.7f, 0.8f, 0.9f, 0.15f);
    glBegin(GL_QUADS);
    glVertex3f(-size, doorHeight, size);
    glVertex3f(size, doorHeight, size);
    glVertex3f(size, height, size);
    glVertex3f(-size, height, size);
    glEnd();

    glDisable(GL_BLEND);
}

void RoomMain::drawMovingDoor() {
    float L = -doorWidth / 2.0f;
    float R = doorWidth / 2.0f;

    glPushMatrix();
    glTranslatef(L, 0.0f, size);
    glRotatef(doorAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-L, 0.0f, 0.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    glColor4f(0.5f, 0.8f, 1.0f, 0.25f);
    glBegin(GL_QUADS);
    glVertex3f(L, 0, 0); glVertex3f(R, 0, 0);
    glVertex3f(R, doorHeight, 0); glVertex3f(L, doorHeight, 0);
    glEnd();

    glDepthMask(GL_TRUE); 

    glColor3f(0.5f, 0.3f, 0.1f);
    float fThick = 0.2f; 
    glBegin(GL_QUADS);
    glVertex3f(L, doorHeight - 0.5f, 0.01f); glVertex3f(R, doorHeight - 0.5f, 0.01f);
    glVertex3f(R, doorHeight, 0.01f); glVertex3f(L, doorHeight, 0.01f);
    glVertex3f(L, 0, 0.01f); glVertex3f(L + 0.4f, 0, 0.01f);
    glVertex3f(L + 0.4f, doorHeight, 0.01f); glVertex3f(L, doorHeight, 0.01f);
    glVertex3f(R - 0.4f, 0, 0.01f); glVertex3f(R, 0, 0.01f);
    glVertex3f(R, doorHeight, 0.01f); glVertex3f(R - 0.4f, doorHeight, 0.01f);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.0f);
    glPushMatrix();
    glTranslatef(R - 0.8f, doorHeight / 2.0f, 0.05f);
    GLUquadric* q = gluNewQuadric();
    gluCylinder(q, 0.1, 0.1, 0.2, 32, 5);
    gluDisk(q, 0, 0.1, 32, 1);
    gluDeleteQuadric(q);
    glPopMatrix();

    glDisable(GL_BLEND);

    glPopMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); 
    printText(-7.0f, doorHeight + 1.1f, size + 2.15f, "CAR SHOWROOM");
}
void RoomMain::Draw() {
    drawBaseStructure();
    drawFrontGlassWall();
    drawMovingDoor();
}
void RoomMain::buildFont(HDC hdc) {
    fontBase = glGenLists(96);
    HFONT font = CreateFont(-24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
        "Arial");
    SelectObject(hdc, font);

    GLYPHMETRICSFLOAT gmf[96];
    wglUseFontOutlines(hdc, 32, 96, fontBase, 0.0f, 0.1f, WGL_FONT_POLYGONS, gmf);
}
void RoomMain::printText(float x, float y, float z, const char* text) {
    if (text == NULL) return;
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(2.0f, 2.0f, 2.0f); 
    glPushAttrib(GL_LIST_BIT);
    glListBase(fontBase - 32);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
    glPopMatrix();
}