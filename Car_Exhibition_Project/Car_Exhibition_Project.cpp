#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Block.h"
#include "Wall.h"
#include "RedPortal.h"
#include "Showroom.h"
#include "texture.h"
#include "Model_3DS.h"
#include "ExternalEnvironment.h"
#include "Sound.h"
#include "Cybertruck.h"
#include <glut.h> 
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "gdi32.lib")

HDC hDC = NULL;
HGLRC hRC = NULL;
HWND hWnd = NULL;

float camX = 0.0f, camY = 15.0f, camZ = 180.0f, camAngleX = 15.0f, camAngleY = 0.0f;
int prevMouseX = 0, prevMouseY = 0;
bool isClicked = false,isNight = false;
GLuint buildingTex,
roadTex, grassTex,
roadTex2, skyboxTex[6],  skyboxNightTex[6],
buildingTexArray1[6],
buildingTexArray2[6],
buildingTexArray3[6], roadTexArray[6], roadTex2Array[6], grassTexArray[6], buildingTexArray4[6];
float showroomWidth = 400.0f, showroomHeight = 70.0f, showroomDepth = 200.0f, glassZPos = showroomDepth / 2.0f, personDoorOpenAngle = 0.0f;
Model_3DS treeModel,plantModel,p1;
ExternalEnvironment myEnv;
Cybertruck myCyber;
Model_3DS* palm;           
GLTexture palmTex[4];       
float carDoorAngle = 0.0f;  
float doorAngle = 0.0f; 
bool isInsideCar = false;
float carSpeed = 0.0f;
//float carX = 0.0f, carZ = 180.0f;
float carAngle = 0.0f;
bool isDriving = false; 
void InitScene();
void RenderScene();
void UpdatePhysics();
float trafficCarPos = 0.0f;
float trafficSpeed = 10.0f;
void ApplyLighting();
void Draw_Skybox(float width, float height, float length);
bool LoadSkybox(GLuint texArray[6], const char* faces[6]);
DirectSoundManager SoundMgr;
DirectSoundBuffer MySound;
float carX = -155.0f; 
float carZ = 165.0f;    
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "CarExhibitionFinal";
    RegisterClass(&wc);

    hWnd = CreateWindow("CarExhibitionFinal", "Modern Car Showroom 2025 ",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        50, 50, 1280, 720, NULL, NULL, hInstance, NULL);

    hDC = GetDC(hWnd);
    PIXELFORMATDESCRIPTOR pfd = { sizeof(pfd), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 24, 0,0,0,0,0,0,0,0,0,0,0,0,0, 24, 0,0, PFD_MAIN_PLANE,0,0,0,0 };
    SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

    InitScene();

    MSG msg;
    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            UpdatePhysics();
            RenderScene();
            SwapBuffers(hDC);
        }
    }
    return (int)msg.wParam;
}
Showroom myShowroom(showroomWidth, showroomHeight, showroomDepth);

bool LoadSkybox(GLuint texArray[6], const char* faces[6]) {
    for (int i = 0; i < 6; i++) {
        texArray[i] = LoadTexture((char*)faces[i], 255);
        if (!texArray[i]) return false;
    }
    return true;
}
 static void LoadTextureToSideArray(GLuint array[6], const char* filename) {
    GLuint tex = LoadTexture((char*)filename, 255);
    for (int i = 0; i < 6; i++) {
        array[i] = tex;
    }
}

void Draw_Skybox(float width, float height, float length)
{
    GLuint* activeSkybox = isNight ? skyboxNightTex : skyboxTex;
    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_TEXTURE_BIT | GL_LIGHTING_BIT | GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    GLfloat mv[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mv);



    glTranslatef(camX, camY, camZ);

    float x = -width / 2.0f;
    float y = -height / 2.0f;
    float z = -length / 2.0f;

    glDisable(GL_LIGHTING);

    glDepthMask(GL_FALSE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_TEXTURE_2D);

    glColor4f(1, 1, 1, 1);

    // FRONT
    glBindTexture(GL_TEXTURE_2D, activeSkybox[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(x, y, z + length);
    glTexCoord2f(1, 1); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0, 1); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0, 0); glVertex3f(x + width, y, z + length);
    glEnd();

    // BACK
    glBindTexture(GL_TEXTURE_2D, activeSkybox[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0); glVertex3f(x + width, y, z);
    glTexCoord2f(1, 1); glVertex3f(x + width, y + height, z);
    glTexCoord2f(0, 1); glVertex3f(x, y + height, z);
    glTexCoord2f(0, 0); glVertex3f(x, y, z);
    glEnd();

    // LEFT
    glBindTexture(GL_TEXTURE_2D, activeSkybox[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1); glVertex3f(x, y + height, z);
    glTexCoord2f(0, 1); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0, 0); glVertex3f(x, y, z + length);
    glTexCoord2f(1, 0); glVertex3f(x, y, z);
    glEnd();

    // RIGHT
    glBindTexture(GL_TEXTURE_2D, activeSkybox[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(x + width, y, z);
    glTexCoord2f(1, 0); glVertex3f(x + width, y, z + length);
    glTexCoord2f(1, 1); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0, 1); glVertex3f(x + width, y + height, z);
    glEnd();

    // UP
    glBindTexture(GL_TEXTURE_2D, activeSkybox[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(x + width, y + height, z);
    glTexCoord2f(1, 0); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(1, 1); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0, 1); glVertex3f(x, y + height, z);
    glEnd();

    // DOWN
    glBindTexture(GL_TEXTURE_2D, activeSkybox[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(x, y, z);
    glTexCoord2f(1, 0); glVertex3f(x, y, z + length);
    glTexCoord2f(1, 1); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0, 1); glVertex3f(x + width, y, z);
    glEnd();

    glDepthMask(GL_TRUE);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glPopMatrix();
    glPopAttrib();
}
static bool checkCollision(float px, float pz, float boxX, float boxZ, float width, float depth) {
    float minX = boxX - (width / 2.0f) - 2.0f; 
    float maxX = boxX + (width / 2.0f) + 2.0f;
    float minZ = boxZ - (depth / 2.0f) - 2.0f;
    float maxZ = boxZ + (depth / 2.0f) + 2.0f;
    if (px >= minX && px <= maxX && pz >= minZ && pz <= maxZ) {
        return true;
    }
    return false;
}
static bool isLocationSafe(float x, float z) {
    if (myEnv.isLocationBlocked(x, z)) return false;

    float halfW = showroomWidth / 2.0f;
    float halfD = showroomDepth / 2.0f;

    float buffer = 3.0f;

    if (z > (glassZPos - buffer) && z < (glassZPos + buffer) && x > -halfW && x < halfW) {
        bool inFrontPortal = (x > -30.0f && x < 30.0f);
        if (!inFrontPortal || (inFrontPortal && myShowroom.portalAngle < 45.0f)) {
            return false;
        }
    }

    if (z < (-halfD + buffer) && z >(-halfD - buffer) && x > -halfW && x < halfW) {
        return false;
    }

    if (x > (halfW - buffer) && x < (halfW + buffer) && z > -halfD && z < halfD) {
        return false;
    }
    float treeRadius = 4.5f;
    if (checkCollision(x, z, (showroomWidth * 0.25f) + 20.0f, (showroomDepth * 0.25f) + 20.0f, treeRadius, treeRadius)) return false;
    if (checkCollision(x, z, (showroomWidth * 0.25f) + 20.0f, (showroomDepth * 0.25f) - 20.0f, treeRadius, treeRadius)) return false;
    if (checkCollision(x, z, -showroomWidth / 2.5f - 20, -showroomDepth / 2.5f, treeRadius, treeRadius)) return false;
    if (checkCollision(x, z, -showroomWidth / 9.0f + 30, -showroomDepth / 2.5f, treeRadius, treeRadius)) return false;
    if (x < (-halfW + buffer) && x >(-halfW - buffer) && z > -halfD && z < halfD) {
        bool inCarDoor = (z > 51.0f && z < 79.0f);
        bool inStairDoor = (z > 85.5f && z < 94.5f);

        if (inCarDoor && myShowroom.carDoorAngle < 5.0f) return false;
        if (inStairDoor && myShowroom.personDoorOpenAngle < 45.0f) return false;
        if (!inCarDoor && !inStairDoor) return false;
    }

    float bWallX = -showroomWidth / 6.0f;
    float bWallZ = -showroomDepth / 9.0f;
    float bWallW = (float)((int)(showroomWidth / 8));
    if (checkCollision(x, z, bWallX, bWallZ, bWallW, 3.0f)) return false;

    float bWall1X = -showroomWidth / 2.0f + 5.0f;
    float bWall1Z = -showroomDepth / 2.0f;
    float bWall1W = (float)((int)(showroomWidth / 8));
    if (checkCollision(x, z, bWall1X, bWall1Z, bWall1W, 8.0f)) return false;
  
    float famW = (showroomWidth / 2.0f) - 15.0f;
    float famD = 93.0f;
    float famCenterX = (showroomWidth / 4.0f) + 5.0f;
    float famCenterZ = (-showroomDepth / 4.0f) + 2.0f;

    if (checkCollision(x, z, famCenterX, famCenterZ, famW, famD)) {

        bool isOpen = (myShowroom.isGlassDoorOpen && myShowroom.glassDoorHeight >= 15.0f);
        bool inDoorWayX = (x > (famCenterX - 80.0f) && x < (famCenterX + 80.0f));

        if (isOpen && inDoorWayX) {
        }
        else {
            return false;
        }
    }


    float advW = (showroomWidth / 2.0f) - 15.0f;
    float advD = 95.0f;
    float advX = (-showroomWidth / 2.0f) + (advW / 2.0f) + 5.0f;

    if (checkCollision(x, z, advX, -showroomDepth * 0.25f, advW, advD)) {
      
        if (!myShowroom.isCarDoorroom1 || myShowroom.doorAlpha > 0.5f) {
            return false;
        }
    }
    float dsX = -showroomWidth * 0.15f;
    float dsZ = showroomDepth * 0.30f;
    float dsW = showroomWidth * 0.20f;
    float dsD = showroomDepth * 0.30f;
    float dsBuffer = 2.5f;
    if (checkCollision(x, z, dsX, dsZ, dsW, dsD)) {
        float backGlassZ = dsZ - (dsD / 2.0f);
        if (z < (backGlassZ + dsBuffer)) return false;

        float rightGlassX = dsX + (dsW / 2.0f);
        if (x > (rightGlassX - dsBuffer)) return false;

        float carCollisionSize = 15.0f;
        if (checkCollision(x, z, dsX, dsZ, carCollisionSize, carCollisionSize)) return false;
    }

   
    float platX = showroomWidth * 0.25f;
    float platZ = showroomDepth * 0.25f;

    if (checkCollision(x, z, platX, platZ, 25.0f, 25.0f)) return false;

  
    float rmCenterX = platX + 10.0f;
    float rmCenterZ = platZ;

    float rmHalfW = 25.0f * 2.3f;  
    float rmHalfD = 25.0f * 1.5f;  
    float rmBuffer = 4.0f;

    if (checkCollision(x, z, rmCenterX, rmCenterZ, rmHalfW * 2, rmHalfD * 2)) {

        float doorWallX = rmCenterX + rmHalfW;

        if (x > (doorWallX - rmBuffer)) {
            bool inDoorWayZ = (z > (rmCenterZ - 11.0f) && z < (rmCenterZ + 18.0f));

            if (inDoorWayZ && myShowroom.myRoom->doorAngle > 45.0f) {
            }
            else {
                return false; 
            }
        }
        else {
            if (x < (rmCenterX - rmHalfW + 2.0f)) return false; 
            if (z > (rmCenterZ + rmHalfD - 2.0f)) return false; 
            if (z < (rmCenterZ - rmHalfD + 2.0f)) return false; 
        }
    }
    float treeXPos[] = { 350.0f, 390.0f, 430.0f };
    for (int i = 0; i < 3; i++) { 
        if (checkCollision(x, z, treeXPos[i], 220.0f, 15.0f, 15.0f)) return false;
    }


    float plantXPos[] = { -150.0f, -210.0f };
    for (int i = 0; i < 2; i++) {
        if (checkCollision(x, z, plantXPos[i], 130.0f, 8.0f, 8.0f)) return false;
    }

    
    float p1XPos[] = { -90.0f, -120.0f, 90.0f, 120.0f };
    for (int i = 0; i < 4; i++) {
        if (checkCollision(x, z, p1XPos[i], 130.0f, 20.0f, 20.0f)) return false;
    }
    float parkingSpacing = 30.0f;
    float parkingLineL = 35.0f;
    float parkingFrontDepth = 150.0f;
    for (float i = -showroomWidth / 2.0f + 40.0f; i <= showroomWidth / 2.0f - 40.0f; i += parkingSpacing) {
        if (abs(i) < 30.0f) continue;

        float globalCarX = i;
        float globalCarZ = glassZPos + (parkingFrontDepth - (parkingLineL / 2.0f) - 4.0f);
        float globalStopperZ = glassZPos + (parkingFrontDepth - 6.0f);

        if (checkCollision(x, z, globalCarX, globalCarZ, 20.0f, 22.0f)) return false; 
        if (checkCollision(x, z, i, globalStopperZ, 10.0f, 2.0f)) return false;      
    }
    float gWidth = 200.0f;
    float gDepth = showroomDepth;
    float gXOffset = (showroomWidth / 2.0f) + (gWidth / 2.0f);

    float carSpacing = 30.0f;
    for (float j = -gDepth / 2.0f + 45.0f; j <= gDepth / 2.0f - 45.0f; j += carSpacing) {
        float localX = (gWidth / 2.0f) - 25.0f;
        float globalX = gXOffset + localX;
        float globalZ = j;

        if (checkCollision(x, z, globalX, globalZ, 12.0f, 18.0f)) {
            return false;
        }
    }

    float safetyMargin = 45.0f;
    float localFrontZ = gDepth / 2.0f - 30.0f;
    float globalFrontZ = localFrontZ; 

    for (float i = -gWidth / 2.0f + safetyMargin; i <= gWidth / 2.0f - safetyMargin; i += carSpacing) {
        if (abs(i) > 40.0f) {
            float globalX = gXOffset + i;
            if (checkCollision(x, z, globalX, globalFrontZ, 15.0f, 12.0f)) {
                return false;
            }
        }
    }

    float bStartX = -gWidth / 2.0f + 10.0f;
    float bEndX = gWidth / 2.0f - 10.0f;
    float globalBollardZ = gDepth / 2.0f + 5.0f;

    for (float i = bStartX; i <= bEndX; i += 15.0f) {
        if (abs(i) < 25.0f) continue;
        float globalBollardX = gXOffset + i;
        if (checkCollision(x, z, globalBollardX, globalBollardZ, 2.0f, 2.0f)) {
            return false;
        }
    }
    return true;
}
void UpdatePhysics() {
    trafficCarPos += trafficSpeed;
    if (trafficCarPos > 900.0f) { 
        trafficCarPos = -900.0f;
    }
    //myShowroom.showcaseCar.wheelRotation -= 2.0f;
    if (isDriving) {
        float nextCarX = carX + sin(carAngle * 3.14159 / 180.0f) * carSpeed;
        float nextCarZ = carZ + cos(carAngle * 3.14159 / 180.0f) * carSpeed;

        if (isLocationSafe(nextCarX, nextCarZ)) {
            carX = nextCarX;
            carZ = nextCarZ;
        }
        else {
            carSpeed = 0;
        }

        camX = carX;
        camZ = carZ;
        camY = 14.0f; 
        camAngleY = carAngle - 180.0f;

        carSpeed *= 0.96;
    }
}

static void drawMovingTraffic(float pos) {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glPushMatrix();
    glTranslatef(pos, 0.0f, 350.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(5.5f, 5.5f, 5.5f);
    myShowroom.myCar.Draw(); 
    glPopMatrix();
    glPushMatrix();
    glTranslatef(pos+400, 0.0f, 380.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(5.5f, 5.5f, 5.5f);
    myShowroom.myCar.Draw(); 
    glPopMatrix();
    glPushMatrix();
    glTranslatef(pos +200.0f, 0.0f, 380.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(5.5f, 5.5f, 5.5f);
    myShowroom.myCar.Draw();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glPushMatrix();
    glTranslatef(-pos+100, 7.0f, 330.0f); 
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f); 
    glScalef(15.0f, 15.0f, 15.0f); 
    myShowroom.showcaseCar.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-pos + 400, 0.0f, 330.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(5.5f, 5.5f, 5.5f);
    myShowroom.myCar.Draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-pos , 7.0f, 300.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glScalef(15.0f, 15.0f, 15.0f);
    myShowroom.showcaseCar.draw();
    glPopMatrix();
    glPopMatrix();
}
 static void DrawVegetation() {
    float treeX[] = { 350.0f, 390.0f, 430.0f };

    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(treeX[i], 0.0f, 220.0f);
        glScalef(5.0f, 5.0f, 5.0f);
        treeModel.Draw();
        glPopMatrix();
    }

    float plantX[] = { -150.0f, -210.0f };

    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(plantX[i], 13.0f, 130.0f);
         glScalef(2.0f, 2.0f, 2.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.82f, 0.78f, 0.60f, 0.5f);

        glDisable(GL_LIGHTING); 

        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.1f);

        plantModel.Draw(); 
  
        glDisable(GL_ALPHA_TEST);
        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 

        glPopMatrix();
    }
    float planX[] = { -90.0f, -120.0f,90.0f, 120.0f };

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(planX[i], 0.0f, 130.0f);
        glRotatef(25.0f, 0, 1, 0);
        glScalef(7.0f, 7.0f, 7.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 0.0f, 0.0f, 0.3f);

        glDisable(GL_LIGHTING);

        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.1f);

        p1.Draw();

        glDisable(GL_ALPHA_TEST);
        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glPopMatrix();
    }
}

void InitScene() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    myShowroom.glassRoomFloorTex = LoadTexture((char*)"floor.bmp", 255);// ++++A
    myShowroom.glassRoomRoofTex = LoadTexture((char*)"ceiling.bmp", 255);// ++++A
    myShowroom.wallBackTex = LoadTexture((char*)"flag.bmp", 255);// ++++A
    myShowroom.floorTex = LoadTexture((char*)"floor2.bmp", 255);
    myShowroom.wallTex = LoadTexture((char*)"wallBlock.bmp", 255);
    myShowroom.wallH = LoadTexture((char*)"wallHadeel.bmp", 255);
    myShowroom.wallTex1 = LoadTexture((char*)"frontOut.bmp", 255);
    myShowroom.carDoorTex = LoadTexture((char*)"ca1111.bmp", 255);
    myShowroom.staffDoorTex = LoadTexture((char*)"door1.bmp", 255);
    myShowroom.asphaltTexture = LoadTexture((char*)"flo1.bmp", 255);
    myShowroom.ceilingTex = LoadTexture((char*)"ceiling.bmp", 255);
    myShowroom.img1 = LoadTexture((char*)"rrr.bmp", 255);
    LoadTextureToSideArray(myEnv.bTex1, "building1.bmp");
    LoadTextureToSideArray(myEnv.bTex2, "building2.bmp");
    LoadTextureToSideArray(myEnv.bTex3, "building3.bmp");
    LoadTextureToSideArray(myEnv.bTex4, "building.bmp");
    LoadTextureToSideArray(myEnv.roadTex, "road4.bmp");
    LoadTextureToSideArray(myEnv.road2Tex, "road111.bmp");
    LoadTextureToSideArray(myEnv.grassTex, "gress.bmp");
    myShowroom.showcaseCar.texBody = LoadTexture((char*)"red.bmp", 255);
    myShowroom.showcaseCar.texWheel = LoadTexture((char*)"carwheel.bmp", 255);
    myShowroom.showcaseCar.texRim = LoadTexture((char*)"rim.bmp", 255);
    myShowroom.showcaseCar.texNumber = LoadTexture((char*)"OIP.bmp", 255);
    GLuint rFloor = LoadTexture((char*)"floorHad.bmp", 255);
    GLuint rCeil = LoadTexture((char*)"Light.bmp", 255);
   
    palm = new Model_3DS();

    if (palm != NULL)
    {
        glEnable(GL_TEXTURE_2D);
        palm->Load((char*)"Palm N280116.3DS");

        if (palm->totalFaces > 0)
        {
            palmTex[0].LoadBMP((char*)"leaf.bmp");
            palmTex[1].LoadBMP((char*)"Arch41_007_bark.bmp");
            palmTex[2].LoadBMP((char*)"Arch41_007_wood.bmp");
            palmTex[3].LoadBMP((char*)"Arch41_007_ground_2.bmp");

            for (int i = 0; i < palm->numMaterials; i++) {
                palm->Materials[i].textured = true;
                if (i == 0)      palm->Materials[i].tex = palmTex[0];
                else if (i == 1) palm->Materials[i].tex = palmTex[1];
                else if (i == 2) palm->Materials[i].tex = palmTex[2];
                else             palm->Materials[i].tex = palmTex[3];
            }
        }
        glDisable(GL_TEXTURE_2D);
    }
    myShowroom.myRoom = new RoomMain(rFloor, myShowroom.wallH, rCeil);
    myShowroom.myRoom->buildFont(hDC);
    const char* faces[6] = {
        "right.bmp",
        "left.bmp",
        "top.bmp",
        "bottom.bmp",
        "front.bmp",
        "back.bmp"
    };


    const char* nightFaces[6] = {
        "night_right.bmp",
        "night_left.bmp",
        "night_top.bmp",
        "night_bottom.bmp",
        "night_front.bmp",
        "night_back.bmp"
    };

    LoadSkybox(skyboxTex, faces);
    LoadSkybox(skyboxNightTex, nightFaces);
    treeModel.Load((char*)"Tree1.3ds");
    plantModel.Load((char*)"Plant 3.3ds");
   
    p1.Load((char*)"Car.3ds");
    glDisable(GL_TEXTURE_2D);
   

    glShadeModel(GL_SMOOTH);
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
    SoundMgr.Initialize(hWnd);
    SoundMgr.CreateSound((char*)"sound3.wav", MySound);
}

void ApplyLighting() {
    glEnable(GL_LIGHTING);

    if (!isNight) {
        GLfloat light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
        GLfloat ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
        GLfloat diffuse[] = { 1.0f, 1.0f, 0.9f, 1.0f };
        GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

        glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
    }
    else {
        // --- إضاءة الليل ---
        // ضوء خافت من القمر
        GLfloat moon_pos[] = { 0.0f, 100.0f, 0.0f, 1.0f };
        GLfloat moon_ambient[] = { 0.05f, 0.05f, 0.1f, 1.0f };
        GLfloat moon_diffuse[] = { 0.2f, 0.2f, 0.4f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, moon_pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, moon_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, moon_diffuse);

        glEnable(GL_LIGHT1);
        GLfloat lamp_pos[] = { 0.0f, 50.0f, 0.0f, 1.0f };
        GLfloat lamp_color[] = { 1.0f, 0.9f, 0.7f, 1.0f };
        glLightfv(GL_LIGHT1, GL_POSITION, lamp_pos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lamp_color);

        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.005f);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0001f);

        glClearColor(0.01f, 0.01f, 0.05f, 1.0f);
    }
}

void RenderScene() {
    RECT rect; GetClientRect(hWnd, &rect);
    glViewport(0, 0, rect.right, rect.bottom);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)rect.right / rect.bottom, 1.0, 2000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(camAngleX, 1, 0, 0);
    glRotatef(camAngleY, 0, 1, 0);
    glTranslatef(-camX, -camY, -camZ);
    Draw_Skybox(4.0f, 4.0f, 4.0f);
    ApplyLighting();
    drawMovingTraffic(trafficCarPos);
    myEnv.render();
    myShowroom.setNightMode(isNight);
    myShowroom.update(camX, camZ);
    myShowroom.render(myCyber);
    glPushMatrix();
    glTranslatef(carX, -0.8f, carZ);
    glRotatef(carAngle, 0.0f, 1.0f, 0.0f);
    glScalef(4.5f, 4.5f, 4.5f); 

    myShowroom.myCar.Draw();
    glPopMatrix();
    DrawVegetation();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(1.0f, 1.0f, 1.0f);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    float speed = 6.5f;
    switch (message) {
    case WM_KEYDOWN:
    {
        float speed = 6.5f;
        float rotationSpeed = 3.0f; 

        if (wParam == VK_LEFT) {
            camAngleY -= rotationSpeed;
        }
        else if (wParam == VK_RIGHT) {
            camAngleY += rotationSpeed;
        }
        else if (wParam == VK_UP) {
            camAngleX -= rotationSpeed;
        }
        else if (wParam == VK_DOWN) {
            camAngleX += rotationSpeed;
        }
        float nextCamX = camX;
        float nextCamZ = camZ;
        float nextCarX = carX;
        float nextCarZ = carZ;

        if (wParam == 'P') {
            isDriving = !isDriving;
            /*if (isDriving) {
                camAngleX = 10.0f;
            }*/
            if (!isDriving) {
                carSpeed = 0.0f;
            }
        }

        if (isDriving) {
            if (wParam == 'W') carSpeed += 0.5f; 
            if (wParam == 'S') carSpeed -= 0.5f;
            if (wParam == 'A') carAngle += 3.0f;  
            if (wParam == 'D') carAngle -= 3.0f;

            if (carSpeed > 5.0f) carSpeed = 5.0f;
            if (carSpeed < -2.0f) carSpeed = -2.0f;
        }
        else {
            if (wParam == 'W') {
                nextCamX += sin(camAngleY * 3.14 / 180) * speed;
                nextCamZ -= cos(camAngleY * 3.14 / 180) * speed;
            }
            else if (wParam == 'S') {
                nextCamX -= sin(camAngleY * 3.14 / 180) * speed;
                nextCamZ += cos(camAngleY * 3.14 / 180) * speed;
            }
            else if (wParam == 'A') {
                nextCamX -= cos(camAngleY * 3.14 / 180) * speed;
                nextCamZ -= sin(camAngleY * 3.14 / 180) * speed;
            }
            else if (wParam == 'D') {
                nextCamX += cos(camAngleY * 3.14 / 180) * speed;
                nextCamZ += sin(camAngleY * 3.14 / 180) * speed;
            }

            if (isLocationSafe(nextCamX, nextCamZ)) {
                camX = nextCamX;
                camZ = nextCamZ;
            }
        }

        if (wParam == '1')
            myShowroom.isGlassDoorOpen = !myShowroom.isGlassDoorOpen;

        if (wParam == 'C') {
            myShowroom.isCarDoorOpening = !myShowroom.isCarDoorOpening;
        }
        if (wParam == '2') {
            myShowroom.isCarDoorroom1 = !myShowroom.isCarDoorroom1;
        }
        if (wParam == 'U') {
            doorAngle += 2.0f;
            if (doorAngle > 90.0f) doorAngle = 90.0f;
            myShowroom.myRoom->setDoorAngle(doorAngle);
        }
        if (wParam == 'R') {
            doorAngle -= 2.0f;
            if (doorAngle < 0.0f) doorAngle = 0.0f;
            myShowroom.myRoom->setDoorAngle(doorAngle);
        }

        if (wParam == 'F') {
            carDoorAngle += 2.0f;
            if (carDoorAngle > 75.0f) carDoorAngle = 75.0f;
            myShowroom.myCar.setDoorAngle(carDoorAngle);
        }
        if (wParam == 'G') {
            carDoorAngle -= 2.0f;
            if (carDoorAngle < 0.0f) carDoorAngle = 0.0f;
            myShowroom.myCar.setDoorAngle(carDoorAngle);
        }

        if (wParam == 'Q') { if (camY < (showroomHeight - 7.0f)) camY += speed; }
        if (wParam == 'E') { if (camY > 5.0f) camY -= speed; }

        if (wParam == 'N') {
            isNight = !isNight;
            myShowroom.setNightMode(isNight);
        }

        if (wParam == 'M') {
            if (MySound.IsPlaying()) MySound.Stop();
            else MySound.Play(true);
        }

        InvalidateRect(hWnd, NULL, FALSE);
    }
    break;
    break;
    case WM_LBUTTONDOWN:
        prevMouseX = LOWORD(lParam);
        prevMouseY = HIWORD(lParam);
        isClicked = true;
        break;
    case VK_ADD:
        showroomWidth += 10.0f;
        showroomDepth += 10.0f;
        break;
    case VK_SUBTRACT:
        showroomWidth -= 10.0f;
        showroomDepth -= 10.0f;
        break;
    case WM_LBUTTONUP: isClicked = false; break;
    case WM_MOUSEMOVE:
        if (isClicked) {
            camAngleY += (LOWORD(lParam) - prevMouseX) * 0.2f;
            camAngleX += (HIWORD(lParam) - prevMouseY) * 0.2f;
            prevMouseX = LOWORD(lParam); prevMouseY = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;
    case WM_DESTROY:
        if (palm) {
            delete palm;
            palm = NULL;
        }
        PostQuitMessage(0); break;
    default: return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}