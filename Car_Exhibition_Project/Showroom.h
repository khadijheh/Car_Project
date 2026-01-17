#pragma once
#ifndef SHOWROOM_H
#define SHOWROOM_H

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>
#include "Wall.h"
#include "RedPortal.h"
#include "Cybertruck.h"
#include "CarModel.h"
#include "Model_3DS.h"

class Showroom {
private:
    float width, height, depth;
    float glassZPos;
    
    bool isNightMode;
    void drawPlatform(float x, float z, float r, float g, float b);
    void drawRealisticCarDoor(float x, float y, float z, float w, float h, float d,float openAngle);
    void drawRealisticStairDoor(float x, float y, float z, float w, float h, float d, float openAngle);
    void drawImprovedLeftWall();
    void drawProfessionalGlass();
    void drawModernFrames();
    void drawSideGlassFrames();
    void drawBackBeam();
  

public:
    CarModel showcaseCar;
    void drawCarDisplaySection(float x, float z);
    void drawTableAndChairs(float x, float z);
    Model_3DS* tableModel;
    float doorPos;    
    float doorAlpha;
    float doorAngle = 0.0f;
    void drawCarShowcase(Cybertruck& car, float x, float z);
    void renderAdvancedGlass(float x, float z, float w, float d, float h);
    void drawFamilyGlassRoom(float x, float z, float w, float d, float h);//++A
    float personDoorOpenAngle;
    int asphaltTexture;
    int floorTex;
    int  wallTex;
    int  wallTex1,img1;
    int ceilingTex;
    void drawFloorTexture(int floorTexID);
    int staffDoorTex;
    int carDoorTex;
    float portalAngle;
    float carDoorAngle;    
    bool isCarDoorOpening;  
    bool isCarDoorroom1;  
    bool isGlassDoorOpen = false;//    +++A
    float glassDoorHeight = 0.0f;   // ارتفاع الباب الحالي
    GLuint glassRoomFloorTex;
    GLuint glassRoomRoofTex;
    GLuint wallBackTex;
    void drawBox(float x, float y, float z, float w, float h, float d, float r, float g, float b, float a = 1.0f);
    Showroom(float w = 400.0f, float h = 60.0f, float d = 200.0f);

    void update(float camX, float camZ); 
    void render(Cybertruck& car);
    void setNightMode(bool night) { isNightMode = night; }

    
    void adjustSize(float deltaW, float deltaD);
};

#endif
#define _CRT_SECURE_NO_WARNINGS