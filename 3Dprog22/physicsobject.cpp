#include "physicsobject.h"

PhysicsObject::PhysicsObject() : mx{0.0f}, my{0.0f}, mz{0.0f}
{

}

PhysicsObject::~PhysicsObject()
{

}

QVector3D PhysicsObject::getVelocity()
{
    return mVelocity;
}

QVector3D PhysicsObject::getAcceleration()
{
    return mAcceleration;
}

void PhysicsObject::setVelocity(QVector3D v)
{
    mVelocity = v;
}

void PhysicsObject::setAcceleration(QVector3D a)
{
    mAcceleration = a;
}

void PhysicsObject::UpdatePosition()
{
    mVelocity += mAcceleration;
    move(mVelocity.x(), mVelocity.y(), mVelocity.z());
}

QVector3D PhysicsObject::getPosition()
{
    return QVector3D{mx, my, mz};
}

float PhysicsObject::getRadius()
{
    return mr;
}

void PhysicsObject::setRadius(float r)
{
    mr = r;
}

void PhysicsObject::move(float dx, float dy, float dz)
{
    mx += dx;
    my += dy;
    mz += dz;
    mMatrix.translate(dx, dy, dz);
}

