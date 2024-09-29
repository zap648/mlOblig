#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "visualobject.h"

class PhysicsObject : public VisualObject
{
private:
    float mx, my, mz, mr;           // posisjon & radius
    QVector3D mAcceleration;     // "    "  "    "   "
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
    void move(QVector3D v) override;

    virtual int type() {} // 0 - plane, 1 - ball, 2 - collisionHandler
};

#endif // PHYSICSOBJECT_H
