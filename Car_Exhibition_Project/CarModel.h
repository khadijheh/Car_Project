#ifndef CARMODEL_H
#define CARMODEL_H

#include <windows.h>
#include <gl/GL.h>
#include <glut.h>
#include <cmath>

class CarModel {
public:
    // متغيرات الحركة والتحكم
    float wheelRotation;
    float steerAngle;
    float doorAngle;
    bool  doorOpen;

    // معرفات التكتشرات (يتم تمريرها من الملف الرئيسي)
    int texBody, texWheel, texRim, texNumber;

    CarModel() {
        wheelRotation = 0.0f;
        steerAngle = 0.0f;
        doorAngle = 0.0f;
        doorOpen = false;
        texBody = texWheel = texRim = texNumber = 0;
    }

    // الدالة الرئيسية لرسم السيارة كاملة
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
    // 1. رسم الظل أسفل السيارة
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

    // 2. رسم جسم السيارة والإضاءة
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
        // Front
        glNormal3f(1, 0, 0);
        glTexCoord2f(0, 0); glVertex3f(1.5f, -0.2f, 0.5f);
        glTexCoord2f(1, 0); glVertex3f(1.5f, -0.2f, -0.5f);
        glTexCoord2f(1, 1); glVertex3f(1.5f, 0.2f, -0.5f);
        glTexCoord2f(0, 1); glVertex3f(1.5f, 0.2f, 0.5f);
        // Back
        glNormal3f(-1, 0, 0);
        glTexCoord2f(0, 0); glVertex3f(-1.1f, -0.2f, 0.5f);
        glTexCoord2f(1, 0); glVertex3f(-1.1f, -0.2f, -0.5f);
        glTexCoord2f(1, 1); glVertex3f(-1.3f, 0.2f, -0.5f);
        glTexCoord2f(0, 1); glVertex3f(-1.3f, 0.2f, 0.5f);
        // Left
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(-1.1f, -0.2f, 0.5f);
        glTexCoord2f(1, 0); glVertex3f(1.5f, -0.2f, 0.5f);
        glTexCoord2f(1, 1); glVertex3f(1.5f, 0.2f, 0.5f);
        glTexCoord2f(0, 1); glVertex3f(-1.3f, 0.2f, 0.5f);
        // Right
        glNormal3f(0, 0, -1);
        glTexCoord2f(0, 0); glVertex3f(-1.1f, -0.2f, -0.5f);
        glTexCoord2f(1, 0); glVertex3f(1.5f, -0.2f, -0.5f);
        glTexCoord2f(1, 1); glVertex3f(1.5f, 0.2f, -0.5f);
        glTexCoord2f(0, 1); glVertex3f(-1.3f, 0.2f, -0.5f);
        // Top Body
        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 0); glVertex3f(-1.3f, 0.2f, 0.5f);
        glTexCoord2f(1, 0); glVertex3f(1.5f, 0.2f, 0.5f);
        glTexCoord2f(1, 1); glVertex3f(1.5f, 0.2f, -0.5f);
        glTexCoord2f(0, 1); glVertex3f(-1.3f, 0.2f, -0.5f);
        glEnd();

        // لوحة الأرقام (OIP)
        glBindTexture(GL_TEXTURE_2D, texNumber);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-0.2f, -0.2f, 0.501f);
        glTexCoord2f(1, 1); glVertex3f(0.2f, -0.2f, 0.501f);
        glTexCoord2f(1, 0); glVertex3f(0.2f, 0.2f, 0.501f);
        glTexCoord2f(0, 0); glVertex3f(-0.2f, 0.2f, 0.501f);
        glEnd();

        drawGlowLights();
        glDisable(GL_TEXTURE_2D);
    }

    // 3. الأضواء المتوهجة (Glow)
    void drawGlowLights() {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        // أضواء أمامية (صفراء بيضاء)
        glColor4f(1.0f, 1.0f, 0.85f, 0.6f);
        glBegin(GL_QUADS);
        glVertex3f(1.51f, -0.05f, 0.35f); glVertex3f(1.51f, -0.05f, 0.15f);
        glVertex3f(1.51f, 0.05f, 0.15f);  glVertex3f(1.51f, 0.05f, 0.35f);
        glVertex3f(1.51f, -0.05f, -0.15f); glVertex3f(1.51f, -0.05f, -0.35f);
        glVertex3f(1.51f, 0.05f, -0.35f);  glVertex3f(1.51f, 0.05f, -0.15f);
        glEnd();

        // أضواء خلفية (حمراء)
        glColor4f(1.0f, 0.0f, 0.0f, 0.6f);
        glBegin(GL_QUADS);
        glVertex3f(-1.21f, -0.05f, 0.35f); glVertex3f(-1.21f, -0.05f, 0.15f);
        glVertex3f(-1.21f, 0.05f, 0.15f);  glVertex3f(-1.21f, 0.05f, 0.35f);
        glEnd();

        glPopAttrib();
    }

    // 4. السقف
    void drawRoof() {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texNumber);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-0.4f, 0.6f, 0.3f);
        glTexCoord2f(0, 1); glVertex3f(0.4f, 0.6f, 0.3f);
        glTexCoord2f(1, 1); glVertex3f(0.4f, 0.6f, -0.3f);
        glTexCoord2f(1, 0); glVertex3f(-0.4f, 0.6f, -0.3f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

    // 5. رسم العجلات ثلاثية الأبعاد
    void drawSolidWheel3D(float radius, float width, int slices) {
        float halfWidth = width * 0.5f;
        float angleStep = 2.0f * 3.14159f / slices;

        // وجه الجنط الأمامي
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texWheel);
        glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0.5f, 0.5f); glVertex3f(0, 0, halfWidth);
        for (int i = 0; i <= slices; i++) {
            float a = i * angleStep;
            glTexCoord2f(0.5f + 0.5f * cos(a), 0.5f + 0.5f * sin(a));
            glVertex3f(radius * cos(a), radius * sin(a), halfWidth);
        }
        glEnd();

        // سطح الإطار (Tread)
        glBindTexture(GL_TEXTURE_2D, texRim);
        glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= slices; i++) {
            float a = i * angleStep;
            float x = cos(a), y = sin(a);
            glNormal3f(x, y, 0);
            glTexCoord2f(i / (float)slices * 3.0f, 0); glVertex3f(radius * x, radius * y, halfWidth);
            glTexCoord2f(i / (float)slices * 3.0f, 1); glVertex3f(radius * x, radius * y, -halfWidth);
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

    void drawWheels() {
        float w = 0.25f, d = 0.15f;
        // Front Left
        glPushMatrix();
        glTranslatef(0.8f, -0.3f, 0.55f);
        glRotatef(steerAngle, 0, 1, 0);
        glRotatef(wheelRotation, 0, 0, 1);
        drawSolidWheel3D(w, d, 32);
        glPopMatrix();
        // Front Right
        glPushMatrix();
        glTranslatef(0.8f, -0.3f, -0.55f);
        glRotatef(steerAngle, 0, 1, 0);
        glRotatef(wheelRotation, 0, 0, 1);
        drawSolidWheel3D(w, d, 32);
        glPopMatrix();
        // Back Wheels (Left & Right)
        glPushMatrix();
        glTranslatef(-0.8f, -0.3f, 0.55f);
        glRotatef(wheelRotation, 0, 0, 1);
        drawSolidWheel3D(w, d, 32);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-0.8f, -0.3f, -0.55f);
        glRotatef(wheelRotation, 0, 0, 1);
        drawSolidWheel3D(w, d, 32);
        glPopMatrix();
    }

    // 6. النوافذ الزجاجية
    void drawWindows() {
        glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);
        glColor4f(0.4f, 0.7f, 0.9f, 0.4f);
        glBegin(GL_QUADS);
        // Front Windshield
        glVertex3f(0.6f, 0.2f, 0.39f); glVertex3f(0.4f, 0.6f, 0.29f);
        glVertex3f(0.4f, 0.6f, -0.29f); glVertex3f(0.6f, 0.2f, -0.39f);
        // Left Window
        glVertex3f(-0.6f, 0.2f, 0.41f); glVertex3f(0.6f, 0.2f, 0.41f);
        glVertex3f(0.4f, 0.6f, 0.31f); glVertex3f(-0.4f, 0.6f, 0.31f);
        glEnd();
        glDepthMask(GL_TRUE);
        glPopAttrib();
    }
};

#endif