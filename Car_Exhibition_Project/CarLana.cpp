#include "CarLana.h"

void CarLana::drawCubeNode() {
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();
}

void CarLana::drawSportWheel() {
    GLUquadric* q = gluNewQuadric();
    glPushMatrix();
    glRotatef(90, 0, 1, 0);

  
    glColor3f(0.05f, 0.05f, 0.05f);
    gluCylinder(q, 0.6, 0.6, 0.5, 32, 5);

    glPushMatrix();
    glTranslatef(0, 0, -0.01f);
    glColor3f(0.7f, 0.7f, 0.7f);
    gluDisk(q, 0, 0.6, 32, 1);
    glPopMatrix();

   
    glPushMatrix();
    glTranslatef(0, 0, 0.51f);
    glColor3f(0.7f, 0.7f, 0.7f);
    gluDisk(q, 0, 0.6, 32, 1);
    glPopMatrix();

    glPopMatrix();
    gluDeleteQuadric(q);
}

void CarLana::Draw() {
    drawPlatform();
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);

    float sportRed[3] = { 0.8f, 0.0f, 0.0f };

    glColor3f(0.1f, 0.1f, 0.1f);
    float zSeats[2] = { 0.8f, -0.8f };
    float xSeats[2] = { -0.7f, 0.7f };
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            glPushMatrix();
            glTranslatef(xSeats[i], 0.8f, zSeats[j]);
            glPushMatrix(); glScalef(0.8f, 0.2f, 0.9f); drawCubeNode(); glPopMatrix();
            glTranslatef(0, 0.4f, -0.3f);
            glPushMatrix(); glScalef(0.7f, 0.8f, 0.15f); drawCubeNode(); glPopMatrix();
            glPopMatrix();
        }
    }

 
    GLUquadric* q = gluNewQuadric();
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.7f, 1.2f, 1.8f);
    glRotatef(+35, 1, 0, 0);
    gluDisk(q, 0.3, 0.35, 25, 1);
    glPopMatrix();

    glColor3fv(sportRed);
    glPushMatrix(); glTranslatef(0, 0.3f, 0); glScalef(4.2f, 0.4f, 9.0f); drawCubeNode(); glPopMatrix();
    glPushMatrix(); glTranslatef(1.6f, 0.8f, 0); glScalef(0.8f, 0.8f, 9.0f); drawCubeNode(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.6f, 0.8f, -1.0f); glScalef(0.8f, 0.8f, 7.0f); drawCubeNode(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.6f, 0.8f, 3.8f); glScalef(0.8f, 0.8f, 1.2f); drawCubeNode(); glPopMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix(); glTranslatef(1.4f, 0.7f, 4.5f); glScalef(0.6f, 0.2f, 0.1f); drawCubeNode(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.4f, 0.7f, 4.5f); glScalef(0.6f, 0.2f, 0.1f); drawCubeNode(); glPopMatrix();
    glPushMatrix();
    glTranslatef(-2.0f, 0.8f, 2.5f);
    glRotatef(carDoorAngle, 0, 1, 0);
    glTranslatef(0.1f, 0, -1.0f);
    glColor3fv(sportRed);
    glPushMatrix(); glScalef(0.15f, 0.8f, 2.5f); drawCubeNode(); glPopMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(-0.1f, 0.2f, -0.6f); glScalef(0.05f, 0.1f, 0.4f); drawCubeNode(); glPopMatrix();
    glPopMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);

    glPushMatrix(); glTranslatef(0, 1.5f, -4.2f); glScalef(3.5f, 0.1f, 0.8f); drawCubeNode(); glPopMatrix();
    glPushMatrix(); glTranslatef(1.5f, 1.0f, -4.2f); glScalef(0.2f, 1.0f, 0.2f); drawCubeNode(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.5f, 1.0f, -4.2f); glScalef(0.2f, 1.0f, 0.2f); drawCubeNode(); glPopMatrix();
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.7f, 0.9f, 1.0f, 0.4f);
    glPushMatrix();
    glTranslatef(0.0f, 1.8f, 2.0f);
    glRotatef(-45, 1, 0, 0); 
    glScalef(3.2f, 1.2f, 0.05f);
    drawCubeNode();
    glPopMatrix();
    glDisable(GL_BLEND);

    float wheelX = 2.1f; float wheelY = -0.1f;
    glPushMatrix(); glTranslatef(-wheelX, wheelY, 2.8f); drawSportWheel(); glPopMatrix();
    glPushMatrix(); glTranslatef(wheelX - 0.5f, wheelY, 2.8f); drawSportWheel(); glPopMatrix();
    glPushMatrix(); glTranslatef(-wheelX, wheelY, -2.8f); drawSportWheel(); glPopMatrix();
    glPushMatrix(); glTranslatef(wheelX - 0.5f, wheelY, -2.8f); drawSportWheel(); glPopMatrix();

    glPopMatrix();
    gluDeleteQuadric(q);
}
void CarLana::drawPlatform() {
    GLUquadric* q = gluNewQuadric();
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(0.0f, 0.02f, 0.0f);
    glRotatef(90, 1, 0, 0);

    glColor3f(0.2f, 0.2f, 0.2f);
    gluDisk(q, 0, 4.5, 64, 1);

    glColor3f(0.4f, 0.4f, 0.4f);
    gluCylinder(q, 4.5, 4.5, 0.3, 64, 1);

    glTranslatef(0, 0, 0.3f);
    gluDisk(q, 0, 4.5, 64, 1);

    glPopMatrix();
    glEnable(GL_LIGHTING);
    gluDeleteQuadric(q);
}
