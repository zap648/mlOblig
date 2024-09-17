#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "visualobject.h"

class PhysicsObject : public VisualObject
{
private:
    QVector3D velocity;         // used to move the object
    QVector3D acceleration;     // "    "  "    "   "
public:
    PhysicsObject();
    ~PhysicsObject();

    QVector3D getVelocity();
    QVector3D getAcceleration();
    void setVelocity(QVector3D v);
    void setAcceleration(QVector3D a);
};

#endif // PHYSICSOBJECT_H
