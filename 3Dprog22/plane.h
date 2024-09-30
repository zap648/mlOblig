#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include "physicsobject.h"

class Plane : public PhysicsObject
{
public:
    Plane();
    Plane(QVector2D size, QQuaternion rotation); // Defunct
    Plane(QVector3D V0, QVector3D V1, QVector3D V2, QVector3D V3);
    ~Plane();

    void init() override;
    void draw(GLint matrixUniform) override;
    int type() override;

    QVector3D getNormal();
    float distanceFromPoint(QVector3D point);
    void Rotate(std::vector<Vertex> vertices, QQuaternion rotation);

    QVector2D size; QQuaternion rotation;
private:
    float mx, my, mz, mr;
    QVector3D normal;
};

#endif // PLANE_H
