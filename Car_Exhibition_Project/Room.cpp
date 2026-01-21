
#include "Room.h"

Room::Room(GLuint f, GLuint w, GLuint c)
    : floorTex(f), wallTex(w), ceilTex(c) {
    size = 25.0f;
    height = 15.0f;
    doorWidth = 6.0f;
    doorHeight = 9.0f;
    doorAngle = 0.0f;
}

void Room::drawBaseStructure() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, floorTex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, 0.0f, size);
    glTexCoord2f(5.0f, 0.0f); glVertex3f(size, 0.0f, size);
    glTexCoord2f(5.0f, 5.0f); glVertex3f(size, 0.0f, -size);
    glTexCoord2f(0.0f, 5.0f); glVertex3f(-size, 0.0f, -size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.7f, 0.8f, 1.0f, 0.8f);

    glBegin(GL_QUADS);
   
    glVertex3f(-size, 0, -size); glVertex3f(size, 0, -size);
    glVertex3f(size, height, -size); glVertex3f(-size, height, -size);

    glVertex3f(-size, 0, size); glVertex3f(-size, 0, -size);
    glVertex3f(-size, height, -size); glVertex3f(-size, height, size);
   
    glVertex3f(size, 0, -size); glVertex3f(size, 0, size);
    glVertex3f(size, height, size); glVertex3f(size, height, -size);
    glEnd();
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ceilTex);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-size, height, size);
    glTexCoord2f(1, 0); glVertex3f(size, height, size);
    glTexCoord2f(1, 1); glVertex3f(size, height, -size);
    glTexCoord2f(0, 1); glVertex3f(-size, height, -size);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Room::drawFrontGlassWall() {

    glLineWidth(5.0f);

    float L = -doorWidth / 2.0f;
    float R = doorWidth / 2.0f;


    glBegin(GL_LINES);

    glColor3f(0.0f, 0.0f, 0.0f);


    glVertex3f(-size, 0, size); glVertex3f(-size, height, size);
    glVertex3f(size, 0, size);  glVertex3f(size, height, size);


    glVertex3f(-size / 2.0f, 0, size); glVertex3f(-size / 2.0f, height, size);
    glVertex3f(size / 2.0f, 0, size);  glVertex3f(size / 2.0f, height, size);

    glVertex3f(-size, 0.1f, size); glVertex3f(size, 0.1f, size);
    glEnd();


    glColor3f(0.15f, 0.15f, 0.15f);
    glPushMatrix();
    glTranslatef(0.0f, height - 1.0f, size + 0.1f);
    glScalef(size * 2.0f, 2.5f, 0.3f); 

    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.0f); glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.0f);   glVertex3f(-0.5f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();


    glColor3f(1.0f, 1.0f, 1.0f);
}

void Room::drawMovingDoor() {
    float L = -doorWidth * 1.5f;
    float R = doorWidth *1.5f;

    glPushMatrix();
    glTranslatef(L, 0.0f, size);
    glRotatef(doorAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-L, 0.0f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5f, 0.7f, 1.0f, 0.4f);
    glBegin(GL_QUADS);
    glVertex3f(L, 0, 0);
    glVertex3f(R, 0, 0);
    glVertex3f(R, doorHeight, 0);
    glVertex3f(L, doorHeight, 0);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f); 
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(L, 0, 0.01f);
    glVertex3f(R, 0, 0.01f);
    glVertex3f(R, doorHeight, 0.01f);
    glVertex3f(L, doorHeight, 0.01f);
    glEnd();
    float handleHeight = doorHeight / 2.0f;
    glColor3f(0.3f, 0.3f, 0.3f); 
    glPushMatrix();
    glTranslatef(R - 0.5f, handleHeight, 0.1f); 
    glScalef(0.2f, 1.2f, 0.2f); 
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.0f); glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.0f);   glVertex3f(-0.5f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
    glPopMatrix();

    glColor3f(1, 1, 1);
}



void Room::Draw() {

    drawBaseStructure();
    drawFrontGlassWall();
    drawMovingDoor();

}


