#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "visualobject.h"

class Cube : public VisualObject
{
private:
    float mx, my, mz, mr;   //position & radius
public:
    Cube();
    Cube(float x, float y, float z, float r, float b, float g);
    ~Cube();

    bool mRotate{true};

    void init() override;
    void draw(GLint matrixUniform) override;
    void move(float x, float y, float z) override;
};

#endif // CUBE_H
