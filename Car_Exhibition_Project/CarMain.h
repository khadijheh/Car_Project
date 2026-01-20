
#include <windows.h>
#include <gl.h>
#include <glu.h>
#include <glaux.h>
#include <cmath>

class CarMain {
private:
    float carDoorAngle;

public:
    CarMain() {
        carDoorAngle = 0.0f;

    }

    void setDoorAngle(float angle) { carDoorAngle = angle; }


    void drawUnitCube();
    void drawWheel();
    void Draw();
};