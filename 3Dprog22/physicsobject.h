#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "visualobject.h"

class PhysicsObject : public VisualObject
{
private:
    float mx, my, mz, mr;           // posisjon & radius
    QVector3D velocity;         // brukt til å røra på Objectet
    QVector3D acceleration;     // "    "  "    "   "
public:
    PhysicsObject();
    ~PhysicsObject();

    QVector3D getVelocity();
    QVector3D getAcceleration();
    void setVelocity(QVector3D v);
    void setAcceleration(QVector3D a);
    void UpdatePosition();
    QVector3D getPosition() override;
    float getRadius() override;
    void setRadius(float r);
    void move(float dx, float dy, float dz) override;
};

#endif // PHYSICSOBJECT_H
