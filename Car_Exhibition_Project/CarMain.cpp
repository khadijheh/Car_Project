#include "CarMain.h"


void CarMain::drawUnitCube() {
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();
}


void CarMain::drawWheel() {
    GLUquadric* q = gluNewQuadric();
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glColor3f(0.1f, 0.1f, 0.1f);
    gluCylinder(q, 0.7, 0.7, 0.5, 30, 5);
    gluDisk(q, 0, 0.7, 30, 1);
    glTranslatef(0, 0, 0.5f);
    gluDisk(q, 0, 0.7, 30, 1);
    glPopMatrix();
    gluDeleteQuadric(q);
}


void CarMain::Draw() {

    glPushMatrix();

    glTranslatef(0.0f, 0.7f, 0.0f);

    float bodyCol[3] = { 0.5f, 0.0f, 0.13f };

    glColor3f(0.15f, 0.15f, 0.15f);
    float zSeats[2] = { 1.0f, -0.8f };
    float xSeats[2] = { -0.6f, 0.6f };
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            glPushMatrix();
            glTranslatef(xSeats[i], 1.6f, zSeats[j]);
            glPushMatrix(); glScalef(0.7f, 0.2f, 0.8f); drawUnitCube(); glPopMatrix();
            glTranslatef(0, 0.5f, -0.3f);
            glPushMatrix(); glScalef(0.6f, 1.0f, 0.15f); drawUnitCube(); glPopMatrix();
            glPopMatrix();
        }
    }

    GLUquadric* q = gluNewQuadric();
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.6f, 2.0f, 2.0f);
    glRotatef(+20, 1, 0, 0);
    gluDisk(q, 0.35, 0.4, 20, 1);
    glPopMatrix();


    glColor3fv(bodyCol);
    glPushMatrix(); glTranslatef(0, 0.5f, 0); glScalef(4.0f, 0.2f, 8.5f); drawUnitCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(1.5f, 1.1f, 0); glScalef(1.0f, 1.0f, 8.5f); drawUnitCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.5f, 1.1f, -1.5f); glScalef(1.0f, 1.0f, 5.5f); drawUnitCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.5f, 1.1f, 3.5f); glScalef(1.0f, 1.0f, 1.5f); drawUnitCube(); glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();

    glTranslatef(0.0f, 1.2f, 4.26f);
    glScalef(1.5f, 0.4f, 0.01f);
    drawUnitCube();
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 0.8f);
    glPushMatrix(); glTranslatef(1.3f, 1.1f, 4.26f); glScalef(0.4f, 0.4f, 0.05f); drawUnitCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.3f, 1.1f, 4.26f); glScalef(0.4f, 0.4f, 0.05f); drawUnitCube(); glPopMatrix();



    glPushMatrix();
    glTranslatef(-2.0f, 1.1f, 2.75f);
    glRotatef(carDoorAngle, 0, 1, 0);
    glTranslatef(0.1f, 0, -1.0f);
    glColor3fv(bodyCol);
    glPushMatrix(); glScalef(0.15f, 1.0f, 2.0f); drawUnitCube(); glPopMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();

    glTranslatef(-0.1f, 0.2f, -0.6f);
    glScalef(0.05f, 0.1f, 0.4f); 
        drawUnitCube();
    glPopMatrix();
    glPopMatrix();


    glColor3fv(bodyCol);
    glPushMatrix(); glTranslatef(0, 3.1f, -0.2f); glScalef(3.0f, 0.2f, 6.5f); drawUnitCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(1.45f, 2.1f, -0.2f); glScalef(0.1f, 1.8f, 6.5f); drawUnitCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.45f, 2.1f, -0.2f); glScalef(0.1f, 1.8f, 6.5f); drawUnitCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 2.1f, -3.45f); glScalef(3.0f, 1.8f, 0.1f); drawUnitCube(); glPopMatrix();


    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(1.6f, 2.5f, 2.7f); glScalef(0.3f, 0.5f, 0.05f); drawUnitCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.6f, 2.5f, 2.7f); glScalef(0.3f, 0.5f, 0.05f); drawUnitCube(); glPopMatrix();


    glColor3fv(bodyCol);
    glPushMatrix(); glTranslatef(0.0f, 1.55f, 3.05f); glScalef(2.8f, 1.1f, 0.05f); drawUnitCube(); glPopMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthMask(GL_FALSE);

    glColor4f(0.6f, 0.8f, 1.0f, 0.4f);

    glPushMatrix();
    glTranslatef(0.0f, 2.6f, 3.05f);
    glScalef(2.8f, 1.0f, 0.05f);
    drawUnitCube();
    glPopMatrix();

    float zWin[2] = { 1.2f, -1.3f };
    for (int i = 0; i < 2; i++) {
        glPushMatrix(); glTranslatef(1.48f, 2.4f, zWin[i]); glScalef(0.05f, 1.0f, 1.8f); drawUnitCube(); glPopMatrix();
        glPushMatrix(); glTranslatef(-1.48f, 2.4f, zWin[i]); glScalef(0.05f, 1.0f, 1.8f); drawUnitCube(); glPopMatrix();
    }

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);


    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix(); glTranslatef(0.5f, 2.3f, 3.1f); glRotatef(-40, 0, 0, 1); glScalef(0.04f, 0.7f, 0.02f); drawUnitCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.5f, 2.3f, 3.1f); glRotatef(-40, 0, 0, 1); glScalef(0.04f, 0.7f, 0.02f); drawUnitCube(); glPopMatrix();


    float wheelX = 2.1f; float wheelY = -0.1f;
    glPushMatrix(); glTranslatef(-wheelX, wheelY, 2.5f); drawWheel(); glPopMatrix();
    glPushMatrix(); glTranslatef(wheelX - 0.5f, wheelY, 2.5f); drawWheel(); glPopMatrix();
    glPushMatrix(); glTranslatef(-wheelX, wheelY, -2.5f); drawWheel(); glPopMatrix();
    glPushMatrix(); glTranslatef(wheelX - 0.5f, wheelY, -2.5f); drawWheel(); glPopMatrix();

    glPopMatrix();
    gluDeleteQuadric(q);
}

