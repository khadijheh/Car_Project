#ifndef REDPORTAL_H
#define REDPORTAL_H

#include <gl/GL.h>
#include <glut.h>

class RedPortal {
public:
    float x, y, z;
    float scaleFactor = 1.5f;
    float doorSwingAngle = 0.0f;
    GLuint bannerTex = 0;
    RedPortal(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

  static  void drawGlowingSign(const char* text, float x, float y, float z, float scale, float brightness)
    {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING); 

        glDisable(GL_BLEND);

        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(scale, scale, scale);
        glScalef(-1.0f, 1.0f, 1.0f);
        glRotatef(180, 0, 1, 0);

       
        float offsetsX[] = { 0.0f, 0.7f, -0.7f, 0.0f, 0.0f };
        float offsetsY[] = { 0.0f, 0.0f, 0.0f, 0.7f, -0.7f };

        for (int j = 0; j < 5; j++) {
            glPushMatrix();
            glTranslatef(offsetsX[j], offsetsY[j], 0.0f);
            for (int i = 0; text[i]; i++) {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
            }
            glPopMatrix();
        }

        glPopMatrix();
        glPopAttrib();
    }
    void drawSingleFaceCentered(float width, float height, float r, float g, float b, float alpha = 1.0f) {
        glColor4f(r, g, b, alpha);
        glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(-width / 2.0f, -height / 2.0f, 0);
        glVertex3f(width / 2.0f, -height / 2.0f, 0);
        glVertex3f(width / 2.0f, height / 2.0f, 0);
        glVertex3f(-width / 2.0f, height / 2.0f, 0);
        glEnd();
    }

    void drawRealisticBlock(float w, float h, float d, int cols, int rows, int depthDivs) {
        float gap = 0.08f;
        float panelW = (w - (gap * (cols - 1))) / cols;
        float panelH = (h - (gap * (rows - 1))) / rows;
        float panelD = (d - (gap * (depthDivs - 1))) / depthDivs;

        glColor3f(0.01f, 0.01f, 0.01f);
        glPushMatrix();
        glTranslatef(0, h / 2.0f, 0);
        glScalef(w - 0.4f, h - 0.4f, d - 0.4f);
        drawSolidCube();
        glPopMatrix();

        for (int r = 0; r < rows; r++) {
            float py = r * (panelH + gap);
            for (int c = 0; c < cols; c++) {
                float px = -w / 2.0f + c * (panelW + gap) + panelW / 2.0f;
                drawSinglePanel(px, py, d / 2.0f + 0.05f, panelW, panelH, 0, 0.9f);
                drawSinglePanel(px, py, -d / 2.0f - 0.05f, panelW, panelH, 180, 0.7f);
            }
            for (int dd = 0; dd < depthDivs; dd++) {
                float pz = -d / 2.0f + dd * (panelD + gap) + panelD / 2.0f;
                drawSinglePanel(w / 2.0f + 0.05f, py, pz, panelD, panelH, 90, 0.8f);
                drawSinglePanel(-w / 2.0f - 0.05f, py, pz, panelD, panelH, -90, 0.8f);
            }
        }

        for (int c = 0; c < cols; c++) {
            for (int dd = 0; dd < depthDivs; dd++) {
                float px = -w / 2.0f + c * (panelW + gap) + panelW / 2.0f;
                float pz = -d / 2.0f + dd * (panelD + gap) + panelD / 2.0f;
                glPushMatrix();
                glTranslatef(px, h + 0.05f, pz);
                glRotatef(90.0f, 1, 0, 0);
                drawSingleFaceCentered(panelW - 0.02f, panelD - 0.02f, 0.85f, 0.05f, 0.05f);
                glPopMatrix();
            }
        }
    }

    void drawDoorFrame(float w, float h, float thickness, float depth) {
        glColor3f(0.05f, 0.05f, 0.05f);
        glPushMatrix();
        glTranslatef(0, h - thickness / 2, 0);
        glScalef(w, thickness, depth);
        drawSolidCube();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, thickness / 2, 0);
        glScalef(w, thickness, depth);
        drawSolidCube();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(w / 2 - thickness / 2, h / 2, 0);
        glScalef(thickness, h, depth);
        drawSolidCube();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-w / 2 + thickness / 2, h / 2, 0);
        glScalef(thickness, h, depth);
        drawSolidCube();
        glPopMatrix();
    }

    void drawUltraRealisticEntrance(float totalW, float totalH, float zPos) {
        for (int i = 0; i < 3; i++) {
            glColor3f(0.8f - (i * 0.05f), 0.8f - (i * 0.05f), 0.75f - (i * 0.05f));
            glPushMatrix();
            glTranslatef(0, -0.4f - (i * 0.6f), zPos + 1.5f - (i * 0.6f));
            glScalef(totalW + 4.0f, 0.6f, 3.0f);
            drawSolidCube();
            glPopMatrix();
        }

        float partW = totalW / 4.0f;
        float frameThickness = 0.25f;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        for (int i = 0; i < 4; i++) {
            float curX = -totalW / 2 + (i * partW) + partW / 2;
            glPushMatrix();
            glTranslatef(curX, 0, zPos);
            drawDoorFrame(partW, totalH, frameThickness, 0.4f);

            glColor4f(0.5f, 0.7f, 0.9f, 0.25f);
            glBegin(GL_QUADS);
            glVertex3f(-partW / 2 + 0.1f, 0.1f, 0.01f);
            glVertex3f(partW / 2 - 0.1f, 0.1f, 0.01f);
            glVertex3f(partW / 2 - 0.1f, totalH - 0.1f, 0.01f);
            glVertex3f(-partW / 2 + 0.1f, totalH - 0.1f, 0.01f);
            glEnd();
            glPopMatrix();

            if (i == 1 || i == 2) {
                float handleSide = (i == 1) ? partW / 2 - 0.4f : -partW / 2 + 0.4f;
                glColor3f(0.15f, 0.15f, 0.15f);
                glPushMatrix();
                glTranslatef(curX + handleSide, totalH * 0.4f, zPos + 0.35f); 
                glScalef(0.15f, totalH * 0.5f, 0.15f);
                drawSolidCube();
                glPopMatrix();
            }
        }
        glDisable(GL_BLEND);
    }

    void drawSinglePanel(float tx, float ty, float tz, float sw, float sh, float ry, float cScale) {
        glPushMatrix();
        glTranslatef(tx, ty, tz);
        glRotatef(ry, 0, 1, 0);
        drawSingleFace(sw, sh, 0.9f * cScale, 0.05f * cScale, 0.05f * cScale);
        glPopMatrix();
    }

    void drawSingleFace(float w, float h, float r, float g, float b) {
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(-w / 2.0f, 0, 0);
        glVertex3f(w / 2.0f, 0, 0);
        glVertex3f(w / 2.0f, h, 0);
        glVertex3f(-w / 2.0f, h, 0);
        glEnd();
    }

    void drawSolidCube() {
        glBegin(GL_QUADS);
        glNormal3f(0, 0, -1); glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f);
        glNormal3f(0, 0, 1); glVertex3f(-0.5f, -0.5f, 0.5f);  glVertex3f(0.5f, -0.5f, 0.5f);  glVertex3f(0.5f, 0.5f, 0.5f);  glVertex3f(-0.5f, 0.5f, 0.5f);
        glNormal3f(0, 1, 0); glVertex3f(-0.5f, 0.5f, -0.5f);  glVertex3f(0.5f, 0.5f, -0.5f);  glVertex3f(0.5f, 0.5f, 0.5f);  glVertex3f(-0.5f, 0.5f, 0.5f);
        glNormal3f(0, -1, 0); glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
        glNormal3f(1, 0, 0); glVertex3f(0.5f, -0.5f, -0.5f);  glVertex3f(0.5f, 0.5f, -0.5f);  glVertex3f(0.5f, 0.5f, 0.5f);  glVertex3f(0.5f, -0.5f, 0.5f);
        glNormal3f(-1, 0, 0); glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
        glEnd();
    }

    void drawModernFrame(float w, float h, float thickness, float depth) {
        glColor3f(0.08f, 0.08f, 0.08f);
        glPushMatrix(); glTranslatef(-w / 2 + thickness / 2, h / 2, 0); glScalef(thickness, h, depth); drawSolidCube(); glPopMatrix();
        glPushMatrix(); glTranslatef(w / 2 - thickness / 2, h / 2, 0); glScalef(thickness, h, depth); drawSolidCube(); glPopMatrix();
        glPushMatrix(); glTranslatef(0, thickness / 2, 0); glScalef(w, thickness, depth); drawSolidCube(); glPopMatrix();
        glPushMatrix(); glTranslatef(0, h - thickness / 2, 0); glScalef(w, thickness, depth); drawSolidCube(); glPopMatrix();
    }
    void drawRealGlassDoor(float totalW, float totalH, float zPos) {
        float doorW = totalW / 4.0f;
        float frameT = 0.12f;
        float transomH = 5.0f;
        float doorH = totalH - transomH;
        float liftAmount = 0.5f;
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        for (int i = 0; i < 4; i++) {
            float curX = -totalW / 2 + (i * doorW) + doorW / 2;

            glPushMatrix();
            glTranslatef(curX, liftAmount, zPos);

            if (i == 1) { 
                glTranslatef(-doorW / 2, 0, 0);     
                glRotatef(-doorSwingAngle, 0, 1, 0); 
                glTranslatef(doorW / 2, 0, 0);      
            }
            else if (i == 2) {
                glTranslatef(doorW / 2, 0, 0);      
                glRotatef(doorSwingAngle, 0, 1, 0); 
                glTranslatef(-doorW / 2, 0, 0);      
            }

            drawModernFrame(doorW, doorH, frameT, 0.2f);

            glColor4f(0.6f, 0.7f, 0.8f, 0.35f);
            glBegin(GL_QUADS);
            glVertex3f(-doorW / 2 + frameT, frameT, 0.01f);
            glVertex3f(doorW / 2 - frameT, frameT, 0.01f);
            glVertex3f(doorW / 2 - frameT, doorH - frameT, 0.01f);
            glVertex3f(-doorW / 2 + frameT, doorH - frameT, 0.01f);
            glEnd();

            if (i == 1 || i == 2) {
                float hSide = (i == 1) ? (doorW / 2 - 0.3f) : (-doorW / 2 + 0.3f);

                glColor3f(0.2f, 0.2f, 0.2f); 
                glPushMatrix();
                glTranslatef(hSide, doorH * 0.3f, 0.2f); 
                glScalef(0.08f, 3.5f, 0.12f);           
                drawSolidCube();
                glPopMatrix();
            }
            glPopMatrix();

            glPushMatrix();
            glTranslatef(curX, doorH, zPos);
            drawModernFrame(doorW, transomH, frameT, 0.2f);

            glColor4f(0.5f, 0.6f, 0.7f, 0.45f);
            glBegin(GL_QUADS);
            glVertex3f(-doorW / 2 + frameT, frameT, 0.01f);
            glVertex3f(doorW / 2 - frameT, frameT, 0.01f);
            glVertex3f(doorW / 2 - frameT, transomH - frameT, 0.01f);
            glVertex3f(-doorW / 2 + frameT, transomH - frameT, 0.01f);
            glEnd();
            glPopMatrix();
        }
        glDisable(GL_BLEND);
    }
    void draw(float wallHeight = 50.0f) {

        glPushMatrix();
        glTranslatef(x, y, z);

      
        float autoScale = wallHeight / 34.0f;
        glScalef(autoScale * scaleFactor, autoScale * scaleFactor, autoScale * scaleFactor);

       
        glPushMatrix();
        glTranslatef(-12.0f, 0, 1.2f);
        drawRealisticBlock(10.0f, 34.0f, 10.0f, 3, 10, 3); 
        glPopMatrix();

        glPushMatrix();
        glTranslatef(12.0f, 0, 1.2f);
        drawRealisticBlock(10.0f, 34.0f, 10.0f, 3, 10, 3);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0, 24.0f, 2.5f);
        drawRealisticBlock(20.0f, 10.0f, 13.0f, 5, 3, 4);

        glTranslatef(0, 5.0f, 6.85f);

        GLfloat emissionDay[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat emissionNight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 

        glMaterialfv(GL_FRONT, GL_EMISSION, emissionNight);

        drawSingleFaceCentered(12.0f, 5.0f, 1.0f, 1.0f, 1.0f);

        glMaterialfv(GL_FRONT, GL_EMISSION, emissionDay);
        drawGlowingSign("CAR", -4.0, -1.5f, 0.15f, 0.03f, 1.0f);
        glPopMatrix();

        glPushMatrix();
        drawRealGlassDoor(20.0f, 24.0f, 0.1f);
        glPopMatrix();
        
        glPopMatrix();
    }
};

#endif