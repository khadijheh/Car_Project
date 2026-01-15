#ifndef CYBERTRUCK_H
#define CYBERTRUCK_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

class Cybertruck {
public:
    void render();

private:
    void drawMainBody();    
    void drawMirrors();
    void drawTopDecks();   
    void drawLightBars();   
    void drawUnderCarriage(); 
    void drawDetailedWheel(float x, float y, float z); 
};

#endif