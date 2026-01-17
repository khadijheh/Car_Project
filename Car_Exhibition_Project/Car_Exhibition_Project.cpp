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
Model_3DS treeModel,plantModel;
ExternalEnvironment myEnv;
Cybertruck myCyber;
void InitScene();
void RenderScene();

void ApplyLighting();
void Draw_Skybox(float width, float height, float length);
bool LoadSkybox(GLuint texArray[6], const char* faces[6]);
DirectSoundManager SoundMgr;
DirectSoundBuffer MySound;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "CarExhibitionFinal";
    RegisterClass(&wc);

    hWnd = CreateWindow("CarExhibitionFinal", "Modern Car Showroom 2025 - Movement Enabled",
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
void LoadTextureToSideArray(GLuint array[6], const char* filename) {
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
bool checkCollision(float px, float pz, float boxX, float boxZ, float width, float depth) {
    float minX = boxX - (width / 2.0f) - 2.0f; // أضفنا 2.0 كفراغ أمان للكاميرا
    float maxX = boxX + (width / 2.0f) + 2.0f;
    float minZ = boxZ - (depth / 2.0f) - 2.0f;
    float maxZ = boxZ + (depth / 2.0f) + 2.0f;

    // إذا كانت الكاميرا داخل هذه الحدود، هناك تصادم
    if (px >= minX && px <= maxX && pz >= minZ && pz <= maxZ) {
        return true;
    }
    return false;
}
bool isLocationSafe(float x, float z) {
    if (myEnv.isLocationBlocked(x, z)) return false;
    // 1. حساب الأبعاد الحالية بناءً على متغيرات الحجم العامة
    float halfW = showroomWidth / 2.0f;
    float halfD = showroomDepth / 2.0f;

    // مسافة أمان (Buffer) لمنع الكاميرا من الالتصاق التام بالأسطح
    float buffer = 3.0f;

    // --- أ. فحص جدران المعرض الأساسية ---

    // الجدار الأمامي (الزجاج والبوابة الحمراء)
    if (z > (glassZPos - buffer) && z < (glassZPos + buffer) && x > -halfW && x < halfW) {
        // فحص إذا كان اللاعب في منطقة البوابة (بين -30 و 30) وهل هي مفتوحة كفاية
        bool inFrontPortal = (x > -30.0f && x < 30.0f);
        if (!inFrontPortal || (inFrontPortal && myShowroom.portalAngle < 45.0f)) {
            return false;
        }
    }

    // الجدار الخلفي الأساسي (عند Z = -halfD)
    if (z < (-halfD + buffer) && z >(-halfD - buffer) && x > -halfW && x < halfW) {
        return false;
    }

    // الجدار الأيمن (عند X = halfW)
    if (x > (halfW - buffer) && x < (halfW + buffer) && z > -halfD && z < halfD) {
        return false;
    }

    // الجدار الأيسر (عند X = -halfW) مع فحص الأبواب (باب السيارة وباب الموظفين)
    if (x < (-halfW + buffer) && x >(-halfW - buffer) && z > -halfD && z < halfD) {
        bool inCarDoor = (z > 51.0f && z < 79.0f);
        bool inStairDoor = (z > 85.5f && z < 94.5f);

        // إذا كان الباب مغلقاً في منطقته -> تصادم
        if (inCarDoor && myShowroom.carDoorAngle < 5.0f) return false;
        if (inStairDoor && myShowroom.personDoorOpenAngle < 45.0f) return false;

        // إذا لم يكن هناك باب أصلاً (منطقة الجدار المصمت)
        if (!inCarDoor && !inStairDoor) return false;
    }


    // --- ب. فحص الجدران الإضافية (التي أضفتها في render) ---

    // الجدار الخلفي الثاني (backWall)
    // الإحداثيات من الكود: x = -width/6, z = -depth/9, width = width/8, thickness = 3.0f
    float bWallX = -showroomWidth / 6.0f;
    float bWallZ = -showroomDepth / 9.0f;
    float bWallW = (float)((int)(showroomWidth / 8));
    if (checkCollision(x, z, bWallX, bWallZ, bWallW, 3.0f)) return false;

    // الجدار الخلفي الأول (backWall1)
    // الإحداثيات: x = -width/2+5, z = -depth/2, width = width/8, thickness = 8.0f
    float bWall1X = -showroomWidth / 2.0f + 5.0f;
    float bWall1Z = -showroomDepth / 2.0f;
    float bWall1W = (float)((int)(showroomWidth / 8));
    if (checkCollision(x, z, bWall1X, bWall1Z, bWall1W, 8.0f)) return false;


    // --- ج. فحص المنصات الداخلية (تعديل الـ 0.25) ---
    // تُرسم المنصات عند ربع العرض والعمق، وحجمها 20x20
    float pX = showroomWidth * 0.25f;
    float pZ = showroomDepth * 0.25f;
    float pSize = 20.0f;

    if (checkCollision(x, z, -pX, -pZ, pSize, pSize)) return false; // منصة 1
    if (checkCollision(x, z, pX, -pZ, pSize, pSize)) return false; // منصة 2
    if (checkCollision(x, z, -pX, pZ, pSize, pSize)) return false; // منصة 3
    if (checkCollision(x, z, pX, pZ, pSize, pSize)) return false; // منصة 4


    // --- د. فحص المباني الخارجية (البيئة المحيطة) ---



    return true; // إذا مر من كل الفحوصات، الموقع آمن
}



void DrawVegetation() {
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
   
    //plantModel.Load((char*)"Cactus.3ds");
   
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
    myEnv.render();
    myShowroom.setNightMode(isNight);
    myShowroom.update(camX, camZ);
    myShowroom.render(myCyber);
 
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
        float nextX = camX;
        float nextZ = camZ;
        if (wParam == '1')//     ++++  A
            myShowroom.isGlassDoorOpen = !myShowroom.isGlassDoorOpen;

        if (wParam == 'W') {
            nextX += sin(camAngleY * 3.14 / 180) * speed;
            nextZ -= cos(camAngleY * 3.14 / 180) * speed;
        }
        else if (wParam == 'S') {
            nextX -= sin(camAngleY * 3.14 / 180) * speed;
            nextZ += cos(camAngleY * 3.14 / 180) * speed;
        }
        else if (wParam == 'A') {
            nextX -= cos(camAngleY * 3.14 / 180) * speed;
            nextZ -= sin(camAngleY * 3.14 / 180) * speed;
        }
        else if (wParam == 'D') {
            nextX += cos(camAngleY * 3.14 / 180) * speed;
            nextZ += sin(camAngleY * 3.14 / 180) * speed;
        }


        if (isLocationSafe(nextX, nextZ)) {
            camX = nextX;
            camZ = nextZ;
        }
        if (wParam == 'Q') {
            if (camY < (showroomHeight - 7.0f)) {
                camY += speed;
            }
        }
        if (wParam == 'E') {

            if (camY > 5.0f) {
                camY -= speed;
            }
        }
        if (wParam == 'N') {
            isNight = !isNight;
            myShowroom.setNightMode(isNight);
        }
        if (wParam == 'C') {
            myShowroom.isCarDoorOpening = !myShowroom.isCarDoorOpening;

        }
        if (wParam == 'R') {
            myShowroom.isCarDoorroom1 = !myShowroom.isCarDoorroom1;

        }
        if (wParam == 'M') {
            if (MySound.IsPlaying()) {
                MySound.Stop();
            }
            else {
                MySound.Play(true);
            }
        }

        InvalidateRect(hWnd, NULL, FALSE);
    }
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
    case WM_DESTROY: PostQuitMessage(0); break;
    default: return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}