#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"
#include <QOpenGLFunctions_4_1_Core>

class Texture : protected QOpenGLFunctions_4_1_Core
{
public:
    Texture();
    ~Texture();
    Texture(char* filePath);

    void LoadTexture();
    void UseTexture();
    void ClearTexture();

private:
    GLuint textureID;
    int width, height, bitDepth;
    char* fileLocation;

    class Logger *mLogger{nullptr};
};

#endif // TEXTURE_H
