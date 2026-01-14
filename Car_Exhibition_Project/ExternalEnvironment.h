#pragma once
#ifndef EXTERNAL_ENVIRONMENT_H
#define EXTERNAL_ENVIRONMENT_H

#include <windows.h>
#include <gl/GL.h>
#include <cmath>
struct ModelInstance {
    float x, y, z, scale;
};
class ExternalEnvironment {
public:
    // مصفوفات الأنسجة (Textures) لكل عناصر البيئة
    GLuint roadTex[6], road2Tex[6], grassTex[6];
    GLuint bTex1[6], bTex2[6], bTex3[6], bTex4[6], skyboxTex[6];

    // مواقع المباني الخلفية المتكررة (X-axis)
    float backX[12] = { 130, 170, 310, 450, 590, 730, -20, -150, -280, -310, -440, -580 };

    // --- دالة مساعدة لفحص التصادم (AABB) ---
    bool checkCollisionInternal(float px, float pz, float bX, float bZ, float bW, float bD) {
        float buffer = 3.0f;
        float halfW = bW / 2.0f;
        float halfD = std::abs(bD) / 2.0f;

        // التصادم يحدد منطقة المبنى فقط
        return (px >= bX - halfW - buffer && px <= bX + halfW + buffer &&
            pz >= bZ - halfD - buffer && pz <= bZ + halfD + buffer);
    }
    // --- دالة الرسم المخصصة (نفس منطق DrawCustomBox الأصلي) ---
    void drawCustomBox(float x, float y, float z, float w, float h, float d, GLuint textures[6]) {
        glPushMatrix();
        glTranslatef(x, y, z);
        glEnable(GL_TEXTURE_2D);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        float repX = w / 100.0f;
        float repY = h / 150.0f;
        float repZ = std::abs(d) / 150.0f;
        float halfW = w / 2.0f;
        float halfD = d / 2.0f;

        // رسم الأوجه الستة وتطبيق الأنسجة المقابلة
        for (int i = 0; i < 6; i++) {
            glBindTexture(GL_TEXTURE_2D, textures[i]);
            glBegin(GL_QUADS);
            if (i == 0) { // Right (X+)
                glNormal3f(1, 0, 0);
                glTexCoord2f(0, 0); glVertex3f(halfW, 0, halfD);
                glTexCoord2f(repZ, 0); glVertex3f(halfW, 0, -halfD);
                glTexCoord2f(repZ, repY); glVertex3f(halfW, h, -halfD);
                glTexCoord2f(0, repY); glVertex3f(halfW, h, halfD);
            }
            else if (i == 1) { // Left (X-)
                glNormal3f(-1, 0, 0);
                glTexCoord2f(0, 0); glVertex3f(-halfW, 0, -halfD);
                glTexCoord2f(repZ, 0); glVertex3f(-halfW, 0, halfD);
                glTexCoord2f(repZ, repY); glVertex3f(-halfW, h, halfD);
                glTexCoord2f(0, repY); glVertex3f(-halfW, h, -halfD);
            }
            else if (i == 2) { // Top (Y+)
                glNormal3f(0, 1, 0);
                glTexCoord2f(0, repZ); glVertex3f(-halfW, h, halfD);
                glTexCoord2f(repX, repZ); glVertex3f(halfW, h, halfD);
                glTexCoord2f(repX, 0); glVertex3f(halfW, h, -halfD);
                glTexCoord2f(0, 0); glVertex3f(-halfW, h, -halfD);
            }
            else if (i == 3) { // Bottom (Y-)
                glNormal3f(0, -1, 0);
                glTexCoord2f(0, 0); glVertex3f(-halfW, 0, -halfD);
                glTexCoord2f(repX, 0); glVertex3f(halfW, 0, -halfD);
                glTexCoord2f(repX, repZ); glVertex3f(halfW, 0, halfD);
                glTexCoord2f(0, repZ); glVertex3f(-halfW, 0, halfD);
            }
            else if (i == 4) { // Front (Z+)
                glNormal3f(0, 0, 1);
                glTexCoord2f(0, 0); glVertex3f(-halfW, 0, halfD);
                glTexCoord2f(repX, 0); glVertex3f(halfW, 0, halfD);
                glTexCoord2f(repX, repY); glVertex3f(halfW, h, halfD);
                glTexCoord2f(0, repY); glVertex3f(-halfW, h, halfD);
            }
            else if (i == 5) { // Back (Z-)
                glNormal3f(0, 0, -1);
                glTexCoord2f(0, 0); glVertex3f(halfW, 0, -halfD);
                glTexCoord2f(repX, 0); glVertex3f(-halfW, 0, -halfD);
                glTexCoord2f(repX, repY); glVertex3f(-halfW, h, -halfD);
                glTexCoord2f(0, repY); glVertex3f(halfW, h, -halfD);
            }
            glEnd();
        }
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }

    // --- دالة الرسم الأساسية ---
    void render() {
        // الطرق (Roads)
        drawCustomBox(120, -0.5f, 250, 600, 0.5f, 50, road2Tex);
        drawCustomBox(-215, -0.5f, 75, 70, 0.5f, 400, road2Tex);
        drawCustomBox(70, -0.5f, 350.5f, 1450, 0.5f, 150, roadTex);

        // العشب (Grass)
        drawCustomBox(360, -0.5f, 150, 120, 0.6f, -150, grassTex);

        // المباني الجانبية (Side Buildings)
        drawCustomBox(480, -0.5f, 200, 120, 100.0f, -150, bTex1);
        drawCustomBox(610, -0.5f, 200, 120, 100.0f, -150, bTex1);
        drawCustomBox(740, -0.5f, 200, 120, 100.0f, -150, bTex2);
        drawCustomBox(-310, -0.5f, 200, 120, 100.0f, -150, bTex2);
        drawCustomBox(-440, -0.5f, 200, 120, 100.0f, -150, bTex3);
        drawCustomBox(-580, -0.5f, 200, 120, 100.0f, -150, bTex3);

        // المباني الخلفية (Loop)
        for (int i = 0; i < 12; i++) {
            drawCustomBox(backX[i], -0.5f, 570, 120, 100.0f, -300, bTex4);
        }
    }

    // --- دالة فحص التصادم الشاملة للبيئة ---
    bool isLocationBlocked(float x, float z) {
        // ملاحظة: استعملنا نفس الأرقام التي تعمل معك في الدالة القديمة تماماً

        // أ. المباني الجانبية
        float bSideZ = 200.0f;
        float bSideDepth = 150.0f;
        if (checkCollisionInternal(x, z, 480, bSideZ, 120, bSideDepth)) return true;
        if (checkCollisionInternal(x, z, 610, bSideZ, 120, bSideDepth)) return true;
        if (checkCollisionInternal(x, z, 740, bSideZ, 120, bSideDepth)) return true;
        if (checkCollisionInternal(x, z, -310, bSideZ, 120, bSideDepth)) return true;
        if (checkCollisionInternal(x, z, -440, bSideZ, 120, bSideDepth)) return true;
        if (checkCollisionInternal(x, z, -580, bSideZ, 120, bSideDepth)) return true;

        // ب. المباني الخلفية (الشارع البعيد)
        float bBackZ = 570.0f;
        float bBackDepth = 300.0f;
        for (int i = 0; i < 12; i++) {
            if (checkCollisionInternal(x, z, backX[i], bBackZ, 120, bBackDepth)) return true;
        }

        return false; // إذا لم يلمس أي مبنى، الشارع مفتوح!
    }
};

#endif