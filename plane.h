#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include "visualobject.h"

class Plane : public VisualObject
{
public:
    Plane();
    ~Plane();

    void init() override;
    void draw(GLint matrixUniform) override;

    float getRadius() override;
private:
    float mx, my, mz, mr;
};

#endif // PLANE_H
