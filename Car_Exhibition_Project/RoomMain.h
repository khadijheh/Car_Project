


#ifndef ROOM_H
#define ROOM_H

#include <windows.h>
#include <gl.h>
#include <glu.h>

class RoomMain {
private:
    GLuint fontBase;
    GLuint floorTex, wallTex, ceilTex;
    float size, height;
    float doorWidth, doorHeight, doorAngle;

public:
    
    RoomMain(GLuint f, GLuint w, GLuint c);
    void buildFont(HDC hdc); 
    void printText(float x, float y, float z, const char* text);
    void drawBaseStructure();
    void drawFrontGlassWall();
    void drawMovingDoor();
    void Draw();

    void setDoorAngle(float angle) { doorAngle = angle; }
};

#endif