#define _CRT_SECURE_NO_WARNINGS
#include "Showroom.h"
#include "OutdoorArea.h"
#include "FrontArea.h"
#include "CornerArea.h"
#include "CurbConnector.h"
extern Cybertruck myCyber;
Showroom::Showroom(float w, float h, float d) {
    width = w;
    height = h;
    depth = d;
    glassZPos = depth / 2.0f;
    personDoorOpenAngle = 0.0f;
    portalAngle = 0.0f;
    isNightMode = false;
}

void Showroom::drawBox(float x, float y, float z, float w, float h, float d, float r, float g, float b, float a) {
    glColor4f(r, g, b, a);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(w, h, d);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1); glVertex3f(-0.5f, 0, 0.5f); glVertex3f(0.5f, 0, 0.5f); glVertex3f(0.5f, 1, 0.5f); glVertex3f(-0.5f, 1, 0.5f);
    glNormal3f(0, 0, -1); glVertex3f(0.5f, 0, -0.5f); glVertex3f(-0.5f, 0, -0.5f); glVertex3f(-0.5f, 1, -0.5f); glVertex3f(0.5f, 1, -0.5f);
    glNormal3f(0, 1, 0); glVertex3f(-0.5f, 1, 0.5f); glVertex3f(0.5f, 1, 0.5f); glVertex3f(0.5f, 1, -0.5f); glVertex3f(-0.5f, 1, -0.5f);
    glNormal3f(0, -1, 0); glVertex3f(-0.5f, 0, -0.5f); glVertex3f(0.5f, 0, -0.5f); glVertex3f(0.5f, 0, 0.5f); glVertex3f(-0.5f, 0, 0.5f);
    glNormal3f(-1, 0, 0); glVertex3f(-0.5f, 0, -0.5f); glVertex3f(-0.5f, 0, 0.5f); glVertex3f(-0.5f, 1, 0.5f); glVertex3f(-0.5f, 1, -0.5f);
    glNormal3f(1, 0, 0); glVertex3f(0.5f, 0, 0.5f); glVertex3f(0.5f, 0, -0.5f); glVertex3f(0.5f, 1, -0.5f); glVertex3f(0.5f, 1, 0.5f);
    glEnd();
    glPopMatrix();
}

void Showroom::drawPlatform(float x, float z, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, 0.1f, z);
    drawBox(0, 0, 0, 40, 0.5f, 40, 0.1f, 0.1f, 0.1f);
    if (isNightMode) drawBox(0, 0.5f, 0, 18, 0.1f, 18, r, g, b, 1.0f);
    else drawBox(0, 0.5f, 0, 18, 0.1f, 18, r, g, b, 0.4f);
    glPopMatrix();
}
void Showroom::drawRealisticCarDoor(float x, float y, float z, float w, float h, float d, float yOffset) {
    glPushMatrix();
    glTranslatef(x, y, z);

    drawBox(-0.5f, h + 0.1f, 0, 1.0f, 1.2f, d + 1.0f, 0.1f, 0.1f, 0.12f);

    drawBox(-0.1f, 0, -(d / 2.0f + 0.2f), 0.3f, h + 0.2f, 0.4f, 0.05f, 0.05f, 0.05f);
    drawBox(-0.1f, 0, (d / 2.0f + 0.2f), 0.3f, h + 0.2f, 0.4f, 0.05f, 0.05f, 0.05f);

    glPushMatrix();

    
    glTranslatef(-0.4f, yOffset, 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, carDoorTex);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -d / 2.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, d / 2.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0, h, d / 2.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0, h, -d / 2.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPopMatrix();
}
void Showroom::drawRealisticStairDoor(float x, float y, float z, float w, float h, float d, float openAngle) {
    glPushMatrix();
    glTranslatef(x, y, z);

    drawBox(-1.0f, 0, 0, 2.0f, 0.5f, d + 2.0f, 0.8f, 0.8f, 0.8f);
    drawBox(-0.5f, 0.5f, 0, 1.5f, 0.5f, d + 1.5f, 0.85f, 0.85f, 0.85f); 

    float doorBaseY = 1.0f;



    glPushMatrix();
    glTranslatef(0, doorBaseY, d / 2.0f); 
    glRotatef(openAngle, 0, 1, 0);
    glTranslatef(0, 0, -d);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, staffDoorTex); 
    glColor3f(1.0f, 1.0f, 1.0f);


    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.7f, 0, 0);  
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.7f, 0, d);  
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.7f, h, d); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.7f, h, 0);  
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glTranslatef(0, 0, d / 2.0F);
    drawBox(-1.2f, h * 0.25f, -d * 0.35f, 0.15f, h * 0.5f, 0.2f, 0.9f, 0.9f, 0.9f);

    glPopMatrix();
    glPopMatrix();
}

void Showroom::drawImprovedLeftWall() {
    float x = -width / 2.0f;
    float splitH = height * 0.45f;
    float wallThickness = 0.8f;
    glPushAttrib(GL_LIGHTING_BIT); 
    float mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f }; 
    float mat_diffuse[] = { 0.15f, 0.15f, 0.15f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
   
    float panelH = (height - splitH) / 4.0f;
    for (int i = 0; i < 4; i++) {
        drawBox(x, splitH + (i * panelH) + 0.2f, 0, 0.9f, panelH - 0.4f, depth, 0.22f, 0.22f, 0.25f);
    }

    float doorAreaD = 80.0f;
    float areaStart = (depth / 2.0f) - doorAreaD;
    float areaEnd = depth / 2.0f;

    float carDoorZ = (depth / 2.0f) - 35.0f;
    float carDoorW = 28.0f;
    float carDoorH = 19.0f;

    float stairDoorZ = (depth / 2.0f) - 10.0f;
    float stairDoorW = 9.0f;
    float stairDoorH = 16.0f;
    float stairDoorBaseY = 1.0f;

    float w1_Len = (carDoorZ - carDoorW / 2.0f) - areaStart;
    if (w1_Len > 0)
        drawBox(x, 0, areaStart + w1_Len / 2.0f, wallThickness, splitH, w1_Len, 0.15f, 0.15f, 0.15f);

    float w2_Start = carDoorZ + carDoorW / 2.0f;
    float w2_End = stairDoorZ - stairDoorW / 2.0f;
    float w2_Len = w2_End - w2_Start;
    if (w2_Len > 0)
        drawBox(x, 0, w2_Start + w2_Len / 2.0f, wallThickness, splitH, w2_Len, 0.15f, 0.15f, 0.15f);

    float w3_Start = stairDoorZ + stairDoorW / 2.0f;
    float w3_Len = areaEnd - w3_Start;
    if (w3_Len > 0)
        drawBox(x, 0, w3_Start + w3_Len / 2.0f, wallThickness, splitH, w3_Len, 0.15f, 0.15f, 0.15f);
    drawBox(x, carDoorH, carDoorZ, wallThickness, splitH - carDoorH, carDoorW, 0.15f, 0.15f, 0.15f);
    float stairTopStart = stairDoorH + stairDoorBaseY;
    drawBox(x, stairTopStart, stairDoorZ, wallThickness, splitH - stairTopStart, stairDoorW, 0.15f, 0.15f, 0.15f);

    drawBox(x, 0, stairDoorZ, wallThickness, stairDoorBaseY, stairDoorW, 0.15f, 0.15f, 0.15f);


    drawRealisticCarDoor(x - 0.1f, 0, carDoorZ, 0.5f, carDoorH, carDoorW, carDoorAngle);
    drawRealisticStairDoor(x - 0.1f, 0, stairDoorZ, 0.5f, stairDoorH, stairDoorW, personDoorOpenAngle);

}

void Showroom::drawProfessionalGlass() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float panelW = 25.0f;
    int numPanels = (int)(width / panelW);

    for (int i = 0; i < numPanels; i++) {
        float xPos = (-width / 2.0f) + (i * panelW) + (panelW / 2.0f);
        if (xPos > -22.0f && xPos < 22.0f) continue;

        drawBox(xPos, 0, glassZPos - 0.1f, panelW - 0.5f, height, 0.1f, 0.1f, 0.15f, 0.2f, 0.25f);
        drawBox(xPos, height * 0.4f, glassZPos + 0.1f, panelW - 0.5f, height * 0.5f, 0.05f, 1.0f, 1.0f, 1.0f, 0.12f);
    }

    drawBox(width / 2.0f - 0.5f, 0, 0, 0.1f, height, depth - 1.0f, 0.1f, 0.15f, 0.2f, 0.3f);

    glDisable(GL_BLEND);
}

void Showroom::drawModernFrames() {
    float halfW = width / 2.0f;
    float zPos = depth / 2.0f;

    drawBox(0, 0.0f, zPos + 1.0f, width + 10.0f, 1.2f, 5.0f, 0.35f, 0.35f, 0.35f); 
    drawBox(0, height - 1.0f, zPos, width + 5.0f, 4.5f, 4.0f, 0.18f, 0.18f, 0.2f); 

    for (float x = -halfW; x <= halfW; x += 25.0f) {
        if (x > -20.0f && x < 20.0f) continue;

        drawBox(x, 0, zPos - 0.8f, 1.0f, height, 1.8f, 0.2f, 0.2f, 0.22f);

        for (float y = 10.0f; y < height - 5.0f; y += 15.0f) {
            glPushMatrix();
            glTranslatef(x, y, zPos + 0.1f);
            drawBox(0, 0, 0, 0.4f, 0.4f, 0.4f, 0.7f, 0.7f, 0.7f); 
            for (int i = 0; i < 4; i++) {
                glPushMatrix();
                glRotatef(45.0f + (i * 90.0f), 0, 0, 1);
                drawBox(0, 0.8f, 0, 0.15f, 1.6f, 0.15f, 0.65f, 0.65f, 0.65f);
                glPopMatrix();
            }
            glPopMatrix();
        }
    }
}
void Showroom::drawFloorTexture(int floorTexID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, floorTexID);
    glColor3f(1.0f, 1.0f, 1.0f); 

    float halfW = width / 2.0f;
    float halfD = depth / 2.0f;

    float repeatX = width / 25.0f;
    float repeatZ = depth / 25.0f;

    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0); 
    glTexCoord2f(0.0f, 0.0f);       glVertex3f(-halfW, 0.01f, -halfD);
    glTexCoord2f(repeatX, 0.0f);    glVertex3f(halfW, 0.01f, -halfD);
    glTexCoord2f(repeatX, repeatZ); glVertex3f(halfW, 0.01f, halfD);
    glTexCoord2f(0.0f, repeatZ);    glVertex3f(-halfW, 0.01f, halfD);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
void Showroom::drawSideGlassFrames() {
    float halfW = width / 2.0f;
    float halfD = depth / 2.0f;
    float frameThickness = 1.2f;

    float carDoorZ = (depth / 2.0f) - 35.0f;
    float carDoorW = 28.0f;
    float gapStart = carDoorZ - (carDoorW / 2.0f);
    float gapEnd = carDoorZ + (carDoorW / 2.0f);

    for (int side : {-1, 1}) { 
        float xPos = side * (halfW - 0.4f);

        drawBox(xPos, height - 1.2f, 0.0f, frameThickness, 1.2f, depth, 0.25f, 0.25f, 0.25f);

        if (side == 1) {
            drawBox(xPos, 0.0f, 0.0f, frameThickness, 1.2f, depth, 0.25f, 0.25f, 0.25f);
        }
        else {
            float part1_Len = gapStart - (-halfD);
            if (part1_Len > 0) {
                float part1_Z = -halfD + (part1_Len / 2.0f);
                drawBox(xPos, 0.0f, part1_Z, frameThickness, 1.2f, part1_Len, 0.25f, 0.25f, 0.25f);
            }
            float part2_Len = halfD - gapEnd;
            if (part2_Len > 0) {
                float part2_Z = gapEnd + (part2_Len / 2.0f);
                drawBox(xPos, 0.0f, part2_Z, frameThickness, 1.2f, part2_Len, 0.25f, 0.25f, 0.25f);
            }
        }

        for (float z = -halfD; z <= halfD; z += 30.0f) {
            drawBox(xPos, 1.2f, z, 0.8f, height - 2.4f, 1.2f, 0.2f, 0.2f, 0.2f);
        }
    }
}
void Showroom::drawBackBeam() {
    float zBack = -(depth / 2.0f) - 2.0f;
    drawBox(0.0f, height, zBack, width + 5.0f, 3.5f, 2.5f, 0.25f, 0.25f, 0.25f);
    drawBox(0.0f, 0.0f, zBack, width + 5.0f, 1.5f, 3.0f, 0.35f, 0.35f, 0.35f);
}

void Showroom::update(float camX, float camZ) {
    // 1. منطق باب الأشخاص (فتح بالدوران بناءً على المسافة)
    float doorPosX = -width / 2.0f;
    float doorPosZ = (depth / 2.0f) - 15.0f;
    float distToPerson = sqrt(pow(camX - doorPosX, 2) + pow(camZ - doorPosZ, 2));

    if (distToPerson < 30.0f) {
        if (personDoorOpenAngle < 90.0f) personDoorOpenAngle += 2.0f;
    }
    else {
        if (personDoorOpenAngle > 0.0f) personDoorOpenAngle -= 2.0f;
    }

    // 2. منطق باب السيارة الجانبي (رفع رأسي - Lift)
    float maxLift = 18.5f;
    if (isCarDoorOpening) {
        if (carDoorAngle < maxLift) carDoorAngle += 0.2f;
    }
    else {
        if (carDoorAngle > 0.0f) carDoorAngle -= 0.2f;
    }

    // 3. منطق الباب الزجاجي المتقدم (الإزاحة + التلاشي التدريجي)
    // ملاحظة: maxGlassMove هي المسافة التي يتحركها قبل أن يختفي تماماً
    float maxGlassMove = 15.0f;
    float glassMoveSpeed = 0.4f;
    float glassFadeSpeed = 0.02f;

    if (isCarDoorroom1) {
        // تحريك لليسا وتلاشي
        if (this->doorPos < maxGlassMove) this->doorPos += glassMoveSpeed;
        if (this->doorAlpha > 0.0f) this->doorAlpha -= glassFadeSpeed;
    }
    else {
        // عودة للمكان وظهور
        if (this->doorPos > 0.0f) this->doorPos -= glassMoveSpeed;
        if (this->doorAlpha < 1.0f) this->doorAlpha += glassFadeSpeed;
    }

    // تصحيح حدود الشفافية لضمان عدم حدوث وميض (Flickering)
    if (this->doorAlpha < 0.0f) this->doorAlpha = 0.0f;
    if (this->doorAlpha > 1.0f) this->doorAlpha = 1.0f;

    // 4. منطق بوابة الـ Portal الحمراء
    float distToPortal = sqrt(pow(camX - 0.0f, 2) + pow(camZ - (glassZPos + 1.5f), 2));
    if (distToPortal < 50.0f) {
        if (portalAngle < 90.0f) portalAngle += 2.0f;
    }
    else {
        if (portalAngle > 0.0f) portalAngle -= 2.0f;
    }
}
void Showroom::render(Cybertruck& car) {
    glEnable(GL_LIGHTING);

    if (isNightMode) {
        GLfloat ambientColor[] = { 0.6f, 0.6f, 0.6f, 1.0f }; 
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

        glEnable(GL_LIGHT0);
        GLfloat lightPos[] = { 0.0f, height - 2.0f, 0.0f, 1.0f };

        GLfloat lightColor[] = { 1.2f, 1.2f, 1.1f, 1.0f };
        GLfloat whiteSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecular);

        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01f);
    }
    else {
        GLfloat ambientDay[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientDay);
        glDisable(GL_LIGHT0);
    }
    drawFloorTexture(this->floorTex);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->ceilingTex);
    glColor3f(1.0f, 1.0f, 1.0f); 

    glPushMatrix();
    glTranslatef(0, height, 0);
    glScalef(width, 2.0f, depth); 

    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0, -0.5f);
    glTexCoord2f(10.0f, 0.0f); glVertex3f(0.5f, 0, -0.5f);
    glTexCoord2f(10.0f, 10.0f); glVertex3f(0.5f, 0, 0.5f);
    glTexCoord2f(0.0f, 10.0f); glVertex3f(-0.5f, 0, 0.5f);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    float gardenWidth = 200.0f;
    float frontDepth = 150.0f;

    float gardenX = (width / 2.0f) + (gardenWidth / 2.0f);
    OutdoorArea garden(gardenX, 0, 0, gardenWidth, depth);
    garden.draw(this, isNightMode);
    
    FrontArea front(0, 0, glassZPos, width, frontDepth);
    front.draw(this, isNightMode);

   
    drawPlatform(width * 0.25f, -depth * 0.25f, 0, 0, 1);
    drawPlatform(-width * 0.25f, depth * 0.25f, 0, 1, 0);
    drawPlatform(width * 0.25f, depth * 0.25f, 1, 1, 0.5f);

    drawImprovedLeftWall();

    drawBackBeam();

    Wall backWall1(-width / 2+5, 0, -depth / 2, (int)(width / 8), (int)(height / 7), 8.0f, 0.0f, 0.0f, 0.0f, this->wallTex);
    backWall1.draw();
    drawCarShowcase(car, -width * 0.25f, -depth * 0.25f);
    Wall backWall(-width / 6, 0, -depth / 9, (int)(width / 8), (int)(height / 6), 3.0f, 1.0f, 1.0f, 1.0f, this->wallTex1);
    //backWall.draw();

    drawSideGlassFrames();
    drawModernFrames();
    drawProfessionalGlass();

    
    if (isNightMode) {
        glEnable(GL_LIGHT2); 
        GLfloat portalLightPos[] = { 0.0f, height + 10.0f, glassZPos + 10.0f, 1.0f };
        GLfloat portalLightDir[] = { 0.0f, -1.0f, -0.8f }; 
        GLfloat portalLightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 

        glLightfv(GL_LIGHT2, GL_POSITION, portalLightPos);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, portalLightColor);
        glLightfv(GL_LIGHT2, GL_SPECULAR, portalLightColor);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, portalLightDir);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0f);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 20.0f); 
    }
    else {
        glDisable(GL_LIGHT2);
    }
    RedPortal portal(0.0f, 0.1f, glassZPos + 1.5f);
    portal.doorSwingAngle = portalAngle;
    portal.draw(height);
    float gardenStartX = width / 2.0f - 10;
    float gardenLength = 121.0f;
    float frontZ = glassZPos + 150.0f;
    float segmentLen = 6.0f; 
    float curveRadius = 12.0f;
    for (float x = gardenStartX; x <= gardenStartX + gardenLength; x += segmentLen) {
        bool isRed = ((int)((x - gardenStartX) / segmentLen) % 2 != 0);

        drawBox(x + 3.0f, 0.05f, frontZ, segmentLen, 1.2f, 2.5f,
            (isRed ? 0.8f : 1.0f), (isRed ? 0.1f : 1.0f), (isRed ? 0.1f : 1.0f), 1.0f);
    }
    float verticalStartX = gardenStartX + gardenLength + segmentLen - 0.8; 
    float verticalZStart = frontZ - curveRadius;
    float verticalLength = 132.0f; 

    for (float z = verticalZStart; z >= verticalZStart - verticalLength; z -= segmentLen) {
        bool isRed = ((int)((verticalZStart - z) / segmentLen) % 2 != 0);

        drawBox(verticalStartX + (curveRadius - 1.25f), 0.05f, z - 3.0f, 2.5f, 1.2f, segmentLen,
            (isRed ? 0.8f : 1.0f), (isRed ? 0.1f : 1.0f), (isRed ? 0.1f : 1.0f), 1.0f);
    }
    CurbConnector connector;
    connector.draw(this, gardenStartX + gardenLength + segmentLen - 2, frontZ - 12.0f, curveRadius);
}
void Showroom::adjustSize(float deltaW, float deltaD) {
    width += deltaW;
    depth += deltaD;
    glassZPos = depth / 2.0f;
}
void Showroom::drawCarShowcase(Cybertruck& car, float x, float z) {
    float gW = (width / 2.0f) - 15.0f; 
    float gD = 130.0f;                 
    float gH = 55.0f;               
    float centerX = (-width / 2.0f) + (gW / 2.0f) + 5.0f;

    glPushMatrix();
    glTranslatef(centerX, gH + 0.1f, z);
    drawBox(0, 0, 0, gW + 4.0f, 0.2f, gD + 4.0f, 0.02f, 0.02f, 0.02f, 1.0f);
    glPopMatrix();

    int gridCount = 5;
    float xStart = centerX - (gW * 0.4f); 
    float xStep = (gW * 0.8f) / (gridCount - 1);

    float zStart = z - (gD * 0.4f); 
    float zStep = (gD * 0.8f) / (gridCount - 1); 

    for (int i = 0; i < gridCount; i++) {
        float lx = xStart + (i * xStep);
        drawBox(lx, gH - 0.15f, z, 0.3f, 0.3f, gD, 0.12f, 0.12f, 0.15f, 1.0f);
    }

    for (int j = 0; j < gridCount; j++) {
        float lz = zStart + (j * zStep);
        drawBox(centerX, gH - 0.15f, lz, gW, 0.3f, 0.3f, 0.12f, 0.12f, 0.15f, 1.0f);
    }

    for (int i = 0; i < gridCount; i++) {
        for (int j = 0; j < gridCount; j++) {
            float lx = xStart + (i * xStep);
            float lz = zStart + (j * zStep);

            glPushMatrix();
            glTranslatef(lx, gH - 0.1f, lz);
            glColor3f(0.08f, 0.08f, 0.08f);
            glPushMatrix(); glScalef(6.0f, 0.4f, 6.0f); glutSolidCube(1.0); glPopMatrix();

            glColor3f(0.3f, 0.3f, 0.3f);
            for (float bx : {-2.5f, 2.5f}) for (float bz : {-2.5f, 2.5f}) {
                glPushMatrix(); glTranslatef(bx, -0.2f, bz); glutSolidSphere(0.12, 8, 8); glPopMatrix();
            }
            glPopMatrix();

            glPushMatrix();
            glTranslatef(lx, gH - 0.3f, lz);
            glRotatef(90, 1, 0, 0);
            glColor3f(0.5f, 0.5f, 0.52f);
            glutSolidCone(2.2, 1.0, 20, 1);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(lx, gH - 0.45f, lz);
            if (isNightMode) glColor3f(1.0f, 1.0f, 0.8f);
            else glColor3f(0.95f, 0.95f, 1.0f);
            glutSolidSphere(0.5, 16, 16);
            glPopMatrix();

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);

            glPushMatrix();
            glTranslatef(lx, gH - 0.45f, lz);
            glColor4f(1.0f, 1.0f, 0.9f, 0.2f);
            glutSolidSphere(1.0, 12, 12);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(lx, gH - 0.05f, lz);
            glRotatef(90, 1, 0, 0);
            glColor4f(1.0f, 0.9f, 0.7f, 0.1f);
            glutSolidTorus(0.1, 3.5, 10, 24);
            glPopMatrix();

            glDisable(GL_BLEND);
        }
    }
    float uniformScale = 9.5f;

    float frontZ = z + 30.0f;
    drawPlatform(centerX, frontZ, 1.0f, 0.0f, 0.0f); 
    glPushMatrix();
    glTranslatef(centerX, 5.8f, frontZ);
    glScalef(uniformScale, uniformScale, uniformScale);
    glRotatef(65.0f, 0, 1, 0);
    car.render();
    glPopMatrix();

    float backZ = z - 10.0f;
    float sideOffset = gW * 0.28f;

    float backPositions[2][2] = {
        {centerX - sideOffset, backZ}, 
        {centerX + sideOffset, backZ} 
    };

    for (int i = 0; i < 2; i++) {
        glPushMatrix();

        glTranslatef(backPositions[i][0], 0.05f, backPositions[i][1]);

        glColor3f(0.08f, 0.08f, 0.08f); 
        glPushMatrix();
        glScalef(40.0f, 0.8f, 22.0f);
        glutSolidCube(1.0);
        glPopMatrix();

        glTranslatef(0.0f, 5.7f, 0.0f);

        glPushMatrix();
        glScalef(uniformScale, uniformScale, uniformScale);

        if (i == 0) glRotatef(35.0f, 0, 1, 0);
        else glRotatef(-35.0f, 0, 1, 0);     

        car.render();
        glPopMatrix();

        glPopMatrix(); 
    }

    renderAdvancedGlass(centerX, z, gW, gD, gH);
}
void Showroom::renderAdvancedGlass(float x, float z, float w, float d, float h) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthMask(GL_TRUE);
    glColor3f(0.1f, 0.1f, 0.1f);
    float cols[4][2] = { {x - w / 2, z - d / 2}, {x + w / 2, z - d / 2}, {x - w / 2, z + d / 2}, {x + w / 2, z + d / 2} };

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(cols[i][0], h / 2, cols[i][1]);
        glScalef(1.8f, h, 1.8f);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(cols[i][0], 0.5f, cols[i][1]);
        glScalef(3.5f, 1.0f, 3.5f);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    for (float level = 0.33f; level <= 1.0f; level += 0.33f) {
        drawBox(x, h * level, z - d / 2, w, 0.8f, 0.8f, 0.1f, 0.1f, 0.1f, 1.0f);
        drawBox(x - w / 2, h * level, z, 0.8f, 0.8f, d, 0.1f, 0.1f, 0.1f, 1.0f);
        drawBox(x + w / 2, h * level, z, 0.8f, 0.8f, d, 0.1f, 0.1f, 0.1f, 1.0f);
    }

    glDepthMask(GL_FALSE);

    float rG = 0.6f, gG = 0.8f, bG = 1.0f, aG = 0.15f;
    drawBox(x, 0, z - d / 2, w, h, 0.1f, rG, gG, bG, aG);
    drawBox(x - w / 2, 0, z, 0.1f, h, d, rG, gG, bG, 0.08f);
    drawBox(x + w / 2, 0, z, 0.1f, h, d, rG, gG, bG, aG);

    glPushMatrix();
    glTranslatef(x, h + 0.2f, z);
    drawBox(0, 0, 0, w - 2.0f, 0.1f, d - 2.0f, rG, gG, bG, 0.3f);
    glPopMatrix();

    static float doorPos = 0.0f;   
    static float doorAlpha = 1.0f; 

    float maxMove = w * 0.20f;

    if (isCarDoorroom1) {
        if (doorPos < maxMove) doorPos += 0.4f; 
        if (doorAlpha > 0.0f) doorAlpha -= 0.02f; 
    }
    else {
        if (doorPos > 0.0f) doorPos -= 0.4f;
        if (doorAlpha < 1.0f) doorAlpha += 0.02f;
    }

    if (doorAlpha > 0.01f) {
        glPushMatrix();
        glTranslatef(x - doorPos, 0, z + d / 2);

        drawBox(0, h / 2, 0, w, h, 0.8f, 0.2f, 0.2f, 0.2f, doorAlpha);
        drawBox(0, 0, 0, w - 1.0f, h, 0.2f, 1.0f, 1.0f, 1.0f, 0.25f * doorAlpha);

        glDepthMask(GL_TRUE);
        glColor4f(0.8f, 0.8f, 0.8f, doorAlpha);
        glPushMatrix();
        glTranslatef(w / 2 - 2.0f, h / 2, 1.0f);
        glScalef(0.5f, 8.0f, 0.5f);
        glutSolidCube(1.0);
        glPopMatrix();
        glDepthMask(GL_FALSE);

        glPopMatrix();
    }

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}