#ifndef CAR_H
#define CAR_H

#include <windows.h>
#include <gl.h>
#include <glu.h>

class CarLana {
private:
    float carDoorAngle;

public:
    float platformRotation = 0.0f; 
    CarLana() { carDoorAngle = 0.0f; }
    void setDoorAngle(float angle) { carDoorAngle = angle; }
    void drawPlatform();
    void drawCubeNode();
    void drawSportWheel();
    void Draw();
};

#endif
