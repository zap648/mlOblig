#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "visualobject.h"
#include <QOpenGLFunctions_4_1_Core>

class HeightMap: public VisualObject
{
public:
    HeightMap(const char* ImagePath);

    void init();
    void draw(GLint matrixUniform);
    float getHeight(QVector2D p);

private:
    GLuint textureID;
    int width, height, bitDepth;
    char* fileLocation;

    class Logger *mLogger{nullptr};

    QVector3D getBarycCoordinate(QVector2D v0, QVector2D v1, QVector2D v2, QVector2D p);
};

#endif // HEIGHTMAP_H
