//#include <windows.h>
//#include "ShowCar1.h"
////#include <glut.h>
//
//#include <GL.H>
//// ===================== المتغيرات الداخلية للصالة =====================
//GLuint img1 = 0;                // ID للـ texture
//float doorAngle = 0.0f;         // زاوية الباب
//const float WORLD_SIZE = 50.0f; // حجم الصالة
//
//// ===================== ShowCar1 =====================
//ShowCar1::ShowCar1() {}
//
//void ShowCar1::draw()
//{
//    drawFloor();
//    drawCeiling();
//    drawWalls();
//    drawColumns();
//    drawFrontWallWithDoor();
//
//    // إضاءة خاصة بالصالة
//    GLfloat emit[] = { 0.2f, 0.2f, 0.2f, 1.0f };
//    glMaterialfv(GL_FRONT, GL_EMISSION, emit);
//    drawSpotlights();
//    GLfloat noEmit[] = { 0, 0, 0, 1 };
//    glMaterialfv(GL_FRONT, GL_EMISSION, noEmit);
//
//    drawCarPlatform();
//}
//
//// ================= FLOOR =================
//void ShowCar1::drawFloor()
//{
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, img1);
//
//    glNormal3f(0, 1, 0);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0, 0); glVertex3f(-WORLD_SIZE, 0, -WORLD_SIZE);
//    glTexCoord2f(5, 0); glVertex3f(WORLD_SIZE, 0, -WORLD_SIZE);
//    glTexCoord2f(5, 5); glVertex3f(WORLD_SIZE, 0, WORLD_SIZE);
//    glTexCoord2f(0, 5); glVertex3f(-WORLD_SIZE, 0, WORLD_SIZE);
//    glEnd();
//
//    glDisable(GL_TEXTURE_2D);
//}
//
//// ================= CEILING =================
//void ShowCar1::drawCeiling()
//{
//    float h = 6.0f;
//    glColor3f(0.85f, 0.85f, 0.85f);
//
//    glBegin(GL_QUADS);
//    glVertex3f(-WORLD_SIZE, h, -WORLD_SIZE);
//    glVertex3f(WORLD_SIZE, h, -WORLD_SIZE);
//    glVertex3f(WORLD_SIZE, h, WORLD_SIZE);
//    glVertex3f(-WORLD_SIZE, h, WORLD_SIZE);
//    glEnd();
//}
//
//// ================= WALLS =================
//void ShowCar1::drawWalls()
//{
//    float h = 6.0f;
//    glColor3f(0.9f, 0.9f, 0.9f);
//
//    // خلفي
//    glBegin(GL_QUADS);
//    glVertex3f(-WORLD_SIZE, 0, -WORLD_SIZE);
//    glVertex3f(WORLD_SIZE, 0, -WORLD_SIZE);
//    glVertex3f(WORLD_SIZE, h, -WORLD_SIZE);
//    glVertex3f(-WORLD_SIZE, h, -WORLD_SIZE);
//    glEnd();
//
//    // يمين
//    glBegin(GL_QUADS);
//    glVertex3f(WORLD_SIZE, 0, -WORLD_SIZE);
//    glVertex3f(WORLD_SIZE, 0, WORLD_SIZE);
//    glVertex3f(WORLD_SIZE, h, WORLD_SIZE);
//    glVertex3f(WORLD_SIZE, h, -WORLD_SIZE);
//    glEnd();
//
//    // يسار
//    glBegin(GL_QUADS);
//    glVertex3f(-WORLD_SIZE, 0, -WORLD_SIZE);
//    glVertex3f(-WORLD_SIZE, 0, WORLD_SIZE);
//    glVertex3f(-WORLD_SIZE, h, WORLD_SIZE);
//    glVertex3f(-WORLD_SIZE, h, -WORLD_SIZE);
//    glEnd();
//}
//
//// ================= COLUMNS =================
//void ShowCar1::drawColumns()
//{
//    glColor3f(0.7f, 0.7f, 0.7f);
//
//    for (int i = -1; i <= 1; i += 2) {
//        for (int j = -1; j <= 1; j += 2) {
//            /*glPushMatrix();
//            glTranslatef(i * 15.0f, 0, j * 15.0f);
//            GLUquadric* q = gluNewQuadric();
//            gluCylinder(q, 0.6, 0.6, 6.0, 20, 20);
//            gluDeleteQuadric(q);
//            glPopMatrix();*/
//        }
//    }
//}
//
//// ================= PLATFORM =================
//void ShowCar1::drawCarPlatform()
//{
//    glColor3f(0.3f, 0.3f, 0.3f);
//    glBegin(GL_QUADS);
//    glVertex3f(-5, 0.02f, -5);
//    glVertex3f(5, 0.02f, -5);
//    glVertex3f(5, 0.02f, 5);
//    glVertex3f(-5, 0.02f, 5);
//    glEnd();
//}
//
//// ================= FRONT WALL + DOOR =================
//void ShowCar1::drawFrontWallWithDoor()
//{
//    float h = 6.0f;
//
//    glPushMatrix();
//    glTranslatef(0, 0, WORLD_SIZE);
//    glRotatef(doorAngle, 0, 1, 0);
//
//    glColor3f(0.6f, 0.6f, 0.6f);
//    glBegin(GL_QUADS);
//    glVertex3f(-5, 0, 0);
//    glVertex3f(5, 0, 0);
//    glVertex3f(5, h, 0);
//    glVertex3f(-5, h, 0);
//    glEnd();
//
//    glPopMatrix();
//}
//
//// ================= SPOTLIGHTS =================
//void ShowCar1::drawSpotlights()
//{
//    glColor3f(1, 1, 0.8f);
//
//    for (int i = -2; i <= 2; i++) {
//        glPushMatrix();
//        glTranslatef(i * 5.0f, 5.8f, 0);
//        //glutSolidSphere(0.2, 10, 10);
//        glPopMatrix();
//    }
//}
