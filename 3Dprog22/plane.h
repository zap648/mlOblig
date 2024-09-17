#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include "physicsobject.h"

class Plane : public PhysicsObject
{
public:
    Plane();
    Plane(float x, float y, float z);
    ~Plane();

    void init() override;
    void draw(GLint matrixUniform) override;

    float getRadius() override;
private:
    float mx, my, mz, mr;
};

#endif // PLANE_H
