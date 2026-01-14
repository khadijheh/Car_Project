#pragma once
#ifndef OUTDOORAREA_H
#define OUTDOORAREA_H

#include <windows.h>
#include <gl/GL.h>

class Showroom; 

class OutdoorArea {
private:
    float x, y, z;
    float width, depth;

    void drawParkingLines(Showroom* s);
    void drawCurb(Showroom* s);
    void drawLamps(Showroom* s, bool isNight);
    void drawSecurityBollards(Showroom* s); 

public:
    OutdoorArea(float _x, float _y, float _z, float _w, float _d);
    void draw(Showroom* showroom, bool isNight);
};

#endif