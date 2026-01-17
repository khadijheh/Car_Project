#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <windows.h>
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
//#include <glut.h>




/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

int num_texture=-1; //Counter to keep track of the last loaded texture



/**********************************************************
 *
 * FUNCTION LoadBitmap(char *)
 *
 * This function loads a bitmap file and return the OpenGL reference ID to use that texture
 *
 *********************************************************/

int LoadTexture(char* filename, int alpha)
{
    int i, j = 0;
    FILE* l_file;
    unsigned char* l_texture;
    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++;

    if ((l_file = fopen(filename, "rb")) == NULL) return (-1);

    fread(&fileheader, sizeof(fileheader), 1, l_file);
    fseek(l_file, sizeof(fileheader), SEEK_SET);
    fread(&infoheader, sizeof(infoheader), 1, l_file);

    // حساب الـ Padding (الحشو) لضمان عدم تشوه الصور
    int width = infoheader.biWidth;
    int height = infoheader.biHeight;
    int padding = (4 - (width * 3) % 4) % 4; // حساب بايتات الحشو في كل سطر

    l_texture = (byte*)malloc(width * height * 4);
    memset(l_texture, 0, width * height * 4);

    for (i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            fread(&rgb, sizeof(rgb), 1, l_file);
            // تصحيح ترتيب الألوان: BMP يقرأ Blue-Green-Red
            l_texture[j + 0] = rgb.rgbtRed;   // Red
            l_texture[j + 1] = rgb.rgbtGreen; // Green
            l_texture[j + 2] = rgb.rgbtBlue;  // Blue
            l_texture[j + 3] = alpha;         // Alpha
            j += 4;
        }
        // القفز فوق بايتات الـ Padding في نهاية كل سطر لكي لا تزحف البكسلات
        fseek(l_file, padding, SEEK_CUR);
    }

    fclose(l_file);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, num_texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // استخدام GL_RGBA لضمان دعم الشفافية
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture);
    return (num_texture);
}

