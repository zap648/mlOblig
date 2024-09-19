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

    QVector3D getNormal();

    float width; float height; float length;
private:
    float mx, my, mz, mr;
    QVector3D normal;
};

#endif // PLANE_H
