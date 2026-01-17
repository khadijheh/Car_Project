#ifndef CARMODEL_H
#define CARMODEL_H

#include <windows.h>
#include <gl/GL.h>
#include <glut.h>
#include <cmath>

class CarModel {
public:
    float wheelRotation;
    float steerAngle;
    float doorAngle;
    bool  doorOpen;

    int texBody, texWheel, texRim, texNumber;

    CarModel() {
        wheelRotation = 0.0f;
        steerAngle = 0.0f;
        doorAngle = 0.0f;
        doorOpen = false;
        texBody = texWheel = texRim = texNumber = 0;
    }

    void draw() {
        glPushMatrix();
        drawShadow();
        drawBody();
        drawRoof();
        drawWheels();
        drawWindows();
        glPopMatrix();
    }

private:
    void drawShadow() {
        glPushAttrib(GL_LIGHTING_BIT | GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);
        glColor4f(0, 0, 0, 0.35f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, -0.49f, 0);
        for (int i = 0; i <= 32; i++) {
            float a = i * 2.0f * 3.14159f / 32;
            glVertex3f(cos(a) * 1.2f, -0.49f, sin(a) * 0.6f);
        }
        glEnd();
        glDepthMask(GL_TRUE);
        glPopAttrib();
    }

    void drawBody() {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texBody);

        GLfloat matDiff[] = { 0.8f, 0.0f, 0.0f, 1.0f };
        GLfloat matSpec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat matShin[] = { 96.0f };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
        glMaterialfv(GL_FRONT, GL_SHININESS, matShin);


        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);

       

        glNormal3f(1, 0, 0);
        glTexCoord2f(0, 0); glVertex3f(1.5f, -0.2f, 0.5f);
        glTexCoord2f(1, 0); glVertex3f(1.5f, -0.2f, -0.5f);
        glTexCoord2f(1, 1); glVertex3f(1.5f, 0.2f, -0.5f);
        glTexCoord2f(0, 1); glVertex3f(1.5f, 0.2f, 0.5f);
        glEnd();

        glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0);
        glTexCoord2f(0, 0); glVertex3f(-1.1f, -0.2f, 0.5f);
        glTexCoord2f(1, 0); glVertex3f(-1.1f, -0.2f, -0.5f);
        glTexCoord2f(1, 1); glVertex3f(-1.3f, 0.2f, -0.5f);
        glTexCoord2f(0, 1); glVertex3f(-1.3f, 0.2f, 0.5f);
        glEnd();
        glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(-1.1f, -0.2f, 0.5f);
        glTexCoord2f(1, 0); glVertex3f(1.5f, -0.2f, 0.5f);
        glTexCoord2f(1, 1); glVertex3f(1.5f, 0.2f, 0.5f);
        glTexCoord2f(0, 1); glVertex3f(-1.3f, 0.2f, 0.5f);
        glEnd();
        glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        glTexCoord2f(0, 0); glVertex3f(-1.1f, -0.2f, -0.5f);
        glTexCoord2f(1, 0); glVertex3f(1.5f, -0.2f, -0.5f);
        glTexCoord2f(1, 1); glVertex3f(1.5f, 0.2f, -0.5f);
        glTexCoord2f(0, 1); glVertex3f(-1.3f, 0.2f, -0.5f);
        glEnd();



        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.3f, 0.2f, 0.5f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.5f, 0.2f, 0.5f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.5f, 0.2f, -0.5f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.3f, 0.2f, -0.5f);
        glEnd();

        glBegin(GL_QUADS);
        glVertex3f(-1.5f, 0.33f, 0.5f);
        glVertex3f(-1.1f, 0.33f, 0.5f);
        glVertex3f(-1.1f, 0.33f, -0.5f);
        glVertex3f(-1.5f, 0.33f, -0.5f);
        glEnd();

        glBegin(GL_QUADS);
        glVertex3f(-1.5f, 0.33f, 0.3f);
        glVertex3f(-1.3f, 0.33f, 0.3f);
        glVertex3f(-1.1f, 0.2f, 0.3f);
        glVertex3f(-1.3f, 0.2f, 0.3f);
        glEnd();


        glBegin(GL_QUADS);
        glVertex3f(-1.5f, 0.33f, -0.3f);
        glVertex3f(-1.3f, 0.33f, -0.3f);
        glVertex3f(-1.1f, 0.2f, -0.3f);
        glVertex3f(-1.3f, 0.2f, -0.3f);
        glEnd();

        glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-1.1f, -0.2f, 0.5f);
        glVertex3f(1.5f, -0.2f, 0.5f);
        glVertex3f(1.5f, -0.2f, -0.5f);
        glVertex3f(-1.1f, -0.2f, -0.5f);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texNumber);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-0.2f, -0.2f, 0.501f);
        glTexCoord2f(1, 1); glVertex3f(0.2f, -0.2f, 0.501f);
        glTexCoord2f(1, 0); glVertex3f(0.2f, 0.2f, 0.501f);
        glTexCoord2f(0, 0); glVertex3f(-0.2f, 0.2f, 0.501f);
        glEnd();
        glBegin(GL_QUADS);
        glTexCoord2f(1, 1); glVertex3f(-0.2f, -0.2f, -0.501f);
        glTexCoord2f(0, 1); glVertex3f(0.2f, -0.2f, -0.501f);
        glTexCoord2f(0, 0); glVertex3f(0.2f, 0.2f, -0.501f);
        glTexCoord2f(1, 0); glVertex3f(-0.2f, 0.2f, -0.501f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        drawGlowLights();

    }

    void drawGlowLights() {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
        glDepthMask(GL_FALSE); 

        for (float z_side : {0.25f, -0.25f}) {
            glColor4f(1.0f, 1.0f, 0.85f, 0.9f);
            glBegin(GL_QUADS);
            glVertex3f(1.51f, -0.05f, z_side + 0.1f);
            glVertex3f(1.51f, -0.05f, z_side - 0.1f);
            glVertex3f(1.51f, 0.05f, z_side - 0.1f);
            glVertex3f(1.51f, 0.05f, z_side + 0.1f);
            glEnd();

            glColor4f(1.0f, 1.0f, 0.8f, 0.3f);
            glBegin(GL_QUADS);
            glVertex3f(1.52f, -0.1f, z_side + 0.15f);
            glVertex3f(1.52f, -0.1f, z_side - 0.15f);
            glVertex3f(1.52f, 0.1f, z_side - 0.15f);
            glVertex3f(1.52f, 0.1f, z_side + 0.15f);
            glEnd();
        }

        glColor4f(1.0f, 0.0f, 0.0f, 0.8f);
        glBegin(GL_QUADS);
        glVertex3f(-1.21f, -0.05f, 0.35f); glVertex3f(-1.21f, -0.05f, 0.15f);
        glVertex3f(-1.21f, 0.05f, 0.15f);  glVertex3f(-1.21f, 0.05f, 0.35f);
        glVertex3f(-1.21f, -0.05f, -0.15f); glVertex3f(-1.21f, -0.05f, -0.35f);
        glVertex3f(-1.21f, 0.05f, -0.35f);  glVertex3f(-1.21f, 0.05f, -0.15f);
        glEnd();

        glDepthMask(GL_TRUE);
        glPopAttrib();
    }
    void drawRoof() {
        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, texNumber);

        glBegin(GL_QUADS);


        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4f, 0.6f, 0.3f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.4f, 0.6f, 0.3f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4f, 0.6f, -0.3f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.4f, 0.6f, -0.3f);

        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

    void drawSolidWheel3D(float radius, float width, int slices) {
        float halfWidth = width * 0.5f;
        float angleStep = 2.0f * 3.14159f / slices;

        glDisable(GL_COLOR_MATERIAL);
        GLfloat tireDiff[] = { 0.9f, 0.9f, 0.9f, 1.0f };
        GLfloat tireSpec[] = { 0.15f, 0.15f, 0.15f, 1.0f };
        GLfloat tireShin[] = { 12.0f };

        glMaterialfv(GL_FRONT, GL_DIFFUSE, tireDiff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, tireSpec);
        glMaterialfv(GL_FRONT, GL_SHININESS, tireShin);

        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texWheel);
        glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.5f, 0.5f);
        glVertex3f(0.0f, 0.0f, halfWidth);
        for (int i = 0; i <= slices; i++) {
            float angle = i * angleStep;
            glTexCoord2f(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));
            glVertex3f(radius * cos(angle), radius * sin(angle), halfWidth);
        }
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texWheel);
        glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0.5f, 0.5f);
        glVertex3f(0.0f, 0.0f, -halfWidth);
        for (int i = 0; i <= slices; i++) {
            float angle = -i * angleStep; 
            glTexCoord2f(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));
            glVertex3f(radius * cos(angle), radius * sin(angle), -halfWidth);
        }
        glEnd();

        glBindTexture(GL_TEXTURE_2D, texRim);
        glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= slices; i++) {
            float angle = i * angleStep;
            float x = cos(angle);
            float y = sin(angle);
            float u = (float)i / slices * 3.0f; 
            glNormal3f(x, y, 0.0f);
            glTexCoord2f(u, 0.0f); glVertex3f(radius * x, radius * y, halfWidth);
            glTexCoord2f(u, 1.0f); glVertex3f(radius * x, radius * y, -halfWidth);
        }
        glEnd();

        glDisable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL); 
    }

    void drawWheels() {
        glDisable(GL_COLOR_MATERIAL);

        GLfloat matDiff[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat matSpec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat matShin[] = { 96.0f };

        glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
        glMaterialfv(GL_FRONT, GL_SHININESS, matShin);

        glColor3f(1.0f, 1.0f, 1.0f);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texWheel);

        float w = 0.25f;
        float d = 0.15f;
        int slices = 48;

        glPushMatrix();
        glTranslatef(0.8f, -0.3f, 0.55f);
        glRotatef(steerAngle, 0, 1, 0);
        glRotatef(wheelRotation, 0, 0, 1);
        drawSolidWheel3D(w, d, slices);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.8f, -0.3f, -0.55f);
        glRotatef(steerAngle, 0, 1, 0);
        glRotatef(wheelRotation, 0, 0, 1);
        drawSolidWheel3D(w, d, slices);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.8f, -0.3f, 0.55f);
        glRotatef(wheelRotation, 0, 0, 1);
        drawSolidWheel3D(w, d, slices);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.8f, -0.3f, -0.55f);
        glRotatef(wheelRotation, 0, 0, 1);
        drawSolidWheel3D(w, d, slices);
        glPopMatrix();

        glEnable(GL_COLOR_MATERIAL);
        glDisable(GL_TEXTURE_2D);
    }
    void drawWindows() {
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);


        glColor4f(0.4f, 0.7f, 0.9f, 0.2f);

        glBegin(GL_QUADS);
        glVertex3f(0.6f, 0.2f, 0.39f);
        glVertex3f(0.4f, 0.6f, 0.29f);
        glVertex3f(0.4f, 0.6f, -0.29f);
        glVertex3f(0.6f, 0.2f, -0.39f);


        glVertex3f(0.6f, 0.2f, -0.39f);
        glVertex3f(0.4f, 0.6f, -0.29f);
        glVertex3f(0.4f, 0.6f, 0.29f);
        glVertex3f(0.6f, 0.2f, 0.39f);


        glVertex3f(-0.6f, 0.2f, 0.39f);
        glVertex3f(-0.4f, 0.6f, 0.29f);
        glVertex3f(-0.4f, 0.6f, -0.29f);
        glVertex3f(-0.6f, 0.2f, -0.39f);

        glVertex3f(-0.6f, 0.2f, -0.39f);
        glVertex3f(-0.4f, 0.6f, -0.29f);
        glVertex3f(-0.4f, 0.6f, 0.29f);
        glVertex3f(-0.6f, 0.2f, 0.39f);

        glVertex3f(-0.6f, 0.2f, 0.41f);
        glVertex3f(0.6f, 0.2f, 0.41f);
        glVertex3f(0.4f, 0.6f, 0.31f);
        glVertex3f(-0.4f, 0.6f, 0.31f);

        glVertex3f(-0.4f, 0.6f, 0.31f);
        glVertex3f(0.4f, 0.6f, 0.31f);
        glVertex3f(0.6f, 0.2f, 0.41f);
        glVertex3f(-0.6f, 0.2f, 0.41f);

        glVertex3f(-0.6f, 0.2f, -0.41f);
        glVertex3f(0.6f, 0.2f, -0.41f);
        glVertex3f(0.4f, 0.6f, -0.31f);
        glVertex3f(-0.4f, 0.6f, -0.31f);

        glVertex3f(-0.4f, 0.6f, -0.31f);
        glVertex3f(0.4f, 0.6f, -0.31f);
        glVertex3f(0.6f, 0.2f, -0.41f);
        glVertex3f(-0.6f, 0.2f, -0.41f);

        glEnd();

        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
    }
};

#endif