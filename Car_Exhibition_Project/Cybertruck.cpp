#include <windows.h>
#include "Cybertruck.h"

void Cybertruck::render() {
    glPushMatrix();

    drawUnderCarriage();
    drawMainBody();
    drawTopDecks();
    drawLightBars();
    drawMirrors();
    drawDetailedWheel(-1.6f, -0.2f, 0.95f);
    drawDetailedWheel(-1.6f, -0.2f, -0.95f);
    drawDetailedWheel(1.6f, -0.2f, 0.95f);
    drawDetailedWheel(1.6f, -0.2f, -0.95f);
    glPopMatrix();
}
void Cybertruck::drawMirrors() {
    float sideZ[] = { 0.92f, -0.92f }; 

    for (int i = 0; i < 2; i++) {
        float z = sideZ[i];
        float offset = (i == 0 ? 0.18f : -0.18f);

        glPushMatrix();

        glColor3f(0.05f, 0.05f, 0.05f);

        glBegin(GL_TRIANGLES);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-1.8f, 0.55f, z);
        glVertex3f(-1.6f, 0.70f, z);
        glVertex3f(-1.6f, 0.55f, z + offset);
        glEnd();

        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-1.8f, 0.55f, z);
        glVertex3f(-1.6f, 0.55f, z + offset);
        glVertex3f(-1.6f, 0.55f, z);
        glEnd();

        glColor3f(0.8f, 0.8f, 0.85f); 
        glBegin(GL_TRIANGLES);
        glNormal3f(1.0f, 0.0f, 0.0f); 
        glVertex3f(-1.6f, 0.55f, z + offset);
        glVertex3f(-1.6f, 0.70f, z);
        glVertex3f(-1.6f, 0.55f, z);
        glEnd();

        glPopMatrix();
    }
}
void Cybertruck::drawMainBody() {
    GLfloat spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat shini[] = { 100.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shini);

    float sideZ[] = { 0.9f, -0.9f };
    for (int i = 0; i < 2; i++) {
        float z = sideZ[i];
        float sideDir = (z > 0 ? 1.0f : -1.0f);

        glColor3f(0.55f, 0.55f, 0.58f);
        glBegin(GL_QUAD_STRIP);
        glNormal3f(0.0f, 0.0f, sideDir);
        glVertex3f(-2.5f, 0.1f, z);  glVertex3f(-2.5f, 0.35f, z);
        glVertex3f(-1.0f, 0.1f, z);  glVertex3f(-1.0f, 0.35f, z);
        glVertex3f(1.0f, 0.1f, z);   glVertex3f(1.0f, 0.35f, z);
        glVertex3f(2.5f, 0.1f, z);   glVertex3f(2.5f, 0.35f, z);
        glEnd();

        glColor3f(0.65f, 0.65f, 0.7f);
        glBegin(GL_POLYGON);
        glNormal3f(0.1f, 0.2f, sideDir);
        glVertex3f(-2.0f, 0.5f, z);
        glVertex3f(0.0f, 1.4f, z);
        glVertex3f(2.5f, 0.6f, z);
        glVertex3f(2.5f, 0.35f, z);
        glVertex3f(-2.0f, 0.35f, z);
        glEnd();

        glColor3f(0.02f, 0.02f, 0.02f);
        glBegin(GL_POLYGON);
        glVertex3f(-1.95f, 0.1f, z * 1.03f);
        glVertex3f(-1.75f, 0.48f, z * 1.03f);
        glVertex3f(-1.15f, 0.48f, z * 1.03f);
        glVertex3f(-0.95f, 0.1f, z * 1.03f);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex3f(1.05f, 0.1f, z * 1.03f);
        glVertex3f(1.25f, 0.48f, z * 1.03f);
        glVertex3f(1.85f, 0.48f, z * 1.03f);
        glVertex3f(2.05f, 0.1f, z * 1.03f);
        glEnd();
    }
}

void Cybertruck::drawTopDecks() {
    glColor3f(0.5f, 0.5f, 0.52f);
    glBegin(GL_QUADS);
    glNormal3f(0.5f, 0.8f, 0.0f);
    glVertex3f(0.0f, 1.4f, 0.9f);  glVertex3f(0.0f, 1.4f, -0.9f);
    glVertex3f(2.5f, 0.6f, -0.9f);  glVertex3f(2.5f, 0.6f, 0.9f);
    glEnd();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.1f, 0.1f, 0.15f, 0.8f); 
    glBegin(GL_QUADS);
    glNormal3f(-0.6f, 0.7f, 0.0f);
    glVertex3f(-2.0f, 0.5f, 0.85f); glVertex3f(-2.0f, 0.5f, -0.85f);
    glVertex3f(0.0f, 1.4f, -0.85f); glVertex3f(0.0f, 1.4f, 0.85f);
    glEnd();

    float sideZ[] = { 0.91f, -0.91f };
    for (int i = 0; i < 2; i++) {
        glColor4f(0.05f, 0.05f, 0.1f, 0.9f);
        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, 0.0f, (sideZ[i] > 0 ? 1.0f : -1.0f));
        glVertex3f(-1.9f, 0.55f, sideZ[i]);
        glVertex3f(0.0f, 1.35f, sideZ[i]);
        glVertex3f(1.5f, 0.75f, sideZ[i]);
        glEnd();
    }
    glDisable(GL_BLEND);
    glLineWidth(2.0f);
    glDisable(GL_LIGHTING);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(-2.0f, 0.5f, 0.9f);
    glVertex3f(0.0f, 1.4f, 0.9f);
    glVertex3f(2.5f, 0.6f, 0.9f);
    glEnd();
    glEnable(GL_LIGHTING);
}
void Cybertruck::drawLightBars() {
    glDisable(GL_LIGHTING);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
    glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(-2.03f, 0.45f, 0.92f);
    glVertex3f(-2.03f, 0.45f, -0.92f);
    glVertex3f(-2.03f, 0.55f, -0.92f);
    glVertex3f(-2.03f, 0.55f, 0.92f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-2.51f, 0.33f, 0.88f);
    glVertex3f(-2.51f, 0.33f, -0.88f);
    glVertex3f(-2.51f, 0.37f, -0.88f);
    glVertex3f(-2.51f, 0.37f, 0.88f);
    glEnd();
    glColor3f(0.9f, 0.9f, 1.0f); 
    float fogY = 0.18f;
    float fogZ[] = { 0.6f, -0.6f };
    for (int i = 0; i < 2; i++) {
        glBegin(GL_QUADS);
        glVertex3f(-2.47f, fogY - 0.02f, fogZ[i] + 0.1f);
        glVertex3f(-2.47f, fogY - 0.02f, fogZ[i] - 0.1f);
        glVertex3f(-2.47f, fogY + 0.02f, fogZ[i] - 0.1f);
        glVertex3f(-2.47f, fogY + 0.02f, fogZ[i] + 0.1f);
        glEnd();
    }

    glColor4f(1.0f, 0.0f, 0.0f, 0.4f);
    glBegin(GL_QUADS);
    glVertex3f(2.53f, 0.56f, 0.92f);
    glVertex3f(2.53f, 0.56f, -0.92f);
    glVertex3f(2.53f, 0.64f, -0.92f);
    glVertex3f(2.53f, 0.64f, 0.92f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(2.54f, 0.59f, 0.88f);
    glVertex3f(2.54f, 0.59f, -0.88f);
    glVertex3f(2.54f, 0.61f, -0.88f);
    glVertex3f(2.54f, 0.61f, 0.88f);
    glEnd();

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}
void Cybertruck::drawUnderCarriage() {
    glColor3f(0.02f, 0.02f, 0.02f);

    glBegin(GL_QUADS);
    glNormal3f(-1.0f, -0.2f, 0.0f);
    glVertex3f(-2.1f, 0.50f, 0.9f);
    glVertex3f(-2.1f, 0.50f, -0.9f);
    glVertex3f(-2.5f, 0.35f, -0.9f);
    glVertex3f(-2.5f, 0.35f, 0.9f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0f, -0.2f, 0.0f);
    glVertex3f(2.5f, 0.6f, 0.9f);
    glVertex3f(2.5f, 0.6f, -0.9f);
    glVertex3f(2.7f, 0.1f, -0.9f); 
    glVertex3f(2.7f, 0.1f, 0.9f);
    glEnd();

    float sideZ[] = { 0.92f, -0.92f };
    for (int i = 0; i < 2; i++) {
        float z = sideZ[i];
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, (z > 0 ? 1.0f : -1.0f));
        glVertex3f(-2.5f, 0.1f, z);
        glVertex3f(2.5f, 0.1f, z);
        glVertex3f(2.5f, 0.25f, z); 
        glVertex3f(-2.5f, 0.25f, z);
        glEnd();
    }

    glColor3f(0.01f, 0.01f, 0.01f);
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(-2.7f, 0.1f, 0.9f);
    glVertex3f(2.7f, 0.1f, 0.9f);
    glVertex3f(2.7f, 0.1f, -0.9f);
    glVertex3f(-2.7f, 0.1f, -0.9f);
    glEnd();
}
void Cybertruck::drawDetailedWheel(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    if (z < 0) glRotatef(180, 0, 1, 0);

    int segments = 8;
    float radius = 0.45f;
    float innerRadius = 0.35f;
    float width = 0.25f;

    glColor3f(0.05f, 0.05f, 0.05f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * 3.14159f / segments;
        float dx = cos(angle) * radius;
        float dy = sin(angle) * radius;
        glNormal3f(dx, dy, 0);
        glVertex3f(dx, dy, width / 2);
        glVertex3f(dx, dy, -width / 2);
    }
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * 3.14159f / segments;
        float dx = cos(angle) * radius;
        float dy = sin(angle) * radius;
        float idx = cos(angle) * innerRadius;
        float idy = sin(angle) * innerRadius;

        glNormal3f(0, 0, 1);
        glVertex3f(dx, dy, width / 2);
        glVertex3f(idx, idy, width / 2 + 0.02f);
    }
    glEnd();

    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    for (int i = 0; i < segments; i++) {
        float angle = i * 2.0f * 3.14159f / segments;
        glVertex3f(cos(angle) * innerRadius, sin(angle) * innerRadius, width / 2 + 0.02f);
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float angle = i * 2.0f * 3.14159f / segments;
        glVertex3f(cos(angle) * 0.1f, sin(angle) * 0.1f, width / 2 + 0.03f);
    }
    glEnd();

    glPopMatrix();
}