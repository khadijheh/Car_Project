
#pragma once
#pragma once
#ifndef SHOWROOM_MANAGER_H
#define SHOWROOM_MANAGER_H

#include <windows.h>
#include <gl/GL.h>

class ShowroomManager {
public:
    float showroomWidth = 500.0f;
    float showroomHeight = 100.0f;
    float showroomDepth = 400.0f;

    void DrawBox(float x, float y, float z, float w, float h, float d, float r, float g, float b) {
        glPushMatrix();
        glTranslatef(x, y / 2.0f, z);
        glColor3f(r, g, b);
        glScalef(w, h, d);
        glBegin(GL_LINE_LOOP); 
        glVertex3f(-0.5, -0.5, -0.5); glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5); glVertex3f(-0.5, 0.5, -0.5);
        glEnd();
        glPopMatrix();
    }
    void DrawPlatform(float x, float z, float r, float g, float b) {
        glPushMatrix();
        glTranslatef(x, 0.5f, z); 
        glColor3f(r, g, b);

        glBegin(GL_QUADS);
        glVertex3f(-10.0f, 0, -10.0f);
        glVertex3f(10.0f, 0, -10.0f);
        glVertex3f(10.0f, 0, 10.0f);
        glVertex3f(-10.0f, 0, 10.0f);
        glEnd();
        glPopMatrix();
    }

    void DrawFourShowrooms() {
        DrawBox(0, showroomHeight, 0, showroomWidth, 2.0f, showroomDepth, 0.15f, 0.15f, 0.15f);

        float platformX = showroomWidth * 0.25f; 
        float platformZ = showroomDepth * 0.25f; 

        DrawPlatform(-platformX, -platformZ, 1, 0, 0);    
        DrawPlatform(platformX, -platformZ, 0, 0, 1);       
        DrawPlatform(-platformX, platformZ, 0, 1, 0);      
        DrawPlatform(platformX, platformZ, 1, 1, 0.5f);     
    }
};

#endif