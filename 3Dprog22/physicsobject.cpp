#include "physicsobject.h"

PhysicsObject::PhysicsObject() : mx{0.0f}, my{0.0f}, mz{0.0f}
{

}

PhysicsObject::~PhysicsObject()
{

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

std::pair<float, float> PhysicsObject::getPosition2D()
{
    return std::pair<float, float>{mx, mz};
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

void PhysicsObject::move(QVector3D v)
{
    mx += v.x();
    my += v.y();
    mz += v.z();
    mMatrix.translate(v.x(), v.y(), v.z());
}

