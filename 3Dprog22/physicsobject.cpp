#include "physicsobject.h"

PhysicsObject::PhysicsObject()
{

}

PhysicsObject::~PhysicsObject()
{

}

QVector3D PhysicsObject::getVelocity()
{

}

QVector3D PhysicsObject::getAcceleration()
{

}

void PhysicsObject::setVelocity(QVector3D v)
{
    velocity = v;
}

void PhysicsObject::setAcceleration(QVector3D a)
{
    acceleration = a;
}
