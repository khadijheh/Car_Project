#include <windows.h>
#include <gl.h>
#include <glu.h>
#include <glaux.h>
#include <cmath>


class Room {
private:
    GLuint floorTex, wallTex, ceilTex;
    float size, height;
   

public:
    float doorWidth, doorHeight, doorAngle;
    Room(GLuint f, GLuint w, GLuint c); 
    void drawBaseStructure();
    void drawFrontGlassWall(); 
    void drawMovingDoor();

    void Draw();
    void setDoorAngle(float angle) { doorAngle = angle; }
};