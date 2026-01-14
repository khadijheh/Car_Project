#include <windows.h>
#include "Block.h"
#include <gl/GL.h>

Block::Block(float px, float py, float pz,
    float s,
    float cr, float cg, float cb)
{
    x = px; y = py; z = pz;
    size = s;
    r = cr; g = cg; b = cb;
}
void Block::draw(int textureID)
{
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(size, size, size);

    glBegin(GL_QUADS);

    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.0f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.0f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 1.0f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 1.0f, 0.5f);

    glNormal3f(0, 0, -1);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.0f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.0f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 1.0f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 1.0f, -0.5f);

    glNormal3f(0, 1, 0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 1.0f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 1.0f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 1.0f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 1.0f, -0.5f);

    glNormal3f(0, -1, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.0f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.0f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.0f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.0f, 0.5f);

    glNormal3f(-1, 0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.0f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.0f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 1.0f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 1.0f, -0.5f);

    glNormal3f(1, 0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.0f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.0f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 1.0f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 1.0f, 0.5f);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}