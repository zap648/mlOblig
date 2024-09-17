#include "physicsobject.h"

PhysicsObject::PhysicsObject() : mx{0.0f}, my{0.0f}, mz{0.0f}
{

}

PhysicsObject::~PhysicsObject()
{

}

QVector3D PhysicsObject::getVelocity()
{
    return velocity;
}

QVector3D PhysicsObject::getAcceleration()
{
    return acceleration;
}

void PhysicsObject::setVelocity(QVector3D v)
{
    velocity = v;
}

void PhysicsObject::setAcceleration(QVector3D a)
{
    acceleration = a;
}

void PhysicsObject::UpdatePosition()
{
    velocity += acceleration;
    mx += velocity.x();
    my += velocity.y();
    mz += velocity.z();
    move(velocity.x(), velocity.y(), velocity.z());
}

QVector3D PhysicsObject::getPosition()
{
    return QVector3D{mx, my, mz};
}

void PhysicsObject::move(float dx, float dy, float dz)
{
    mx += dx;
    my += dy;
    mz += dz;
    mMatrix.translate(dx, dy, dz);
}

