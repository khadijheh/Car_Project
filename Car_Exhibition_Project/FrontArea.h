#ifndef FRONTAREA_H
#define FRONTAREA_H

#include "Showroom.h"
#include <vector>

class FrontArea {
public:
    
    float x, y, z;
    float width, depth;

    FrontArea(float _x, float _y, float _z, float _w, float _d);
    void draw(Showroom* s, bool isNight);

private:
  
  void  drawCurbCurve(Showroom* s, float centerX, float centerZ, float radius);
    void drawAsphalt(Showroom* s);
    void drawMainCurb(Showroom* s);      
    void drawParkingSlots(Showroom* s);  
    void drawGreenBelts(Showroom* s);   
    void drawGroundCurve(
        Showroom* s,
        float centerX,
        float centerZ,
        float innerRadius,
        float outerRadius,
        float height,
        float r, float g, float b
    );
    void drawAsphaltCurve(Showroom* s, float centerX, float centerZ, float radius);
};

#endif