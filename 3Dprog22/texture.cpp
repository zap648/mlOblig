#include "texture.h"
#include <iostream>
#include <string>
#include "logger.h"

Texture::Texture()
{
    initializeOpenGLFunctions();
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = nullptr;
}

Texture::Texture(char* filePath)
{
    initializeOpenGLFunctions();
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = filePath;
}

Texture::~Texture()
{
    ClearTexture();
}

void Texture::ClearTexture()
{
    glDeleteTextures(1, &textureID);
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = nullptr;
}

void Texture::LoadTexture()
{
    mLogger = Logger::getInstance();
    initializeOpenGLFunctions();

    // Flips image
    stbi_set_flip_vertically_on_load(true);

    //const char* file = fileLocation.c_str;
    unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
    std::cout << fileLocation << std::endl;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // S and T are also known as U and V, another name being X and Y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    if (texData) // If the texture data we provided is valid...
    {
        // ... then load the texture...
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
        mLogger->logText("Succesfully loaded texture image");
    }
    else
    {
        // ... otherwise something went wrong and we need to report it.
        mLogger->logText("Could not load texture image", LogType::REALERROR);
    }
    stbi_image_free(texData);
}

void Texture::UseTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}
