#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "octaball.h"
#include "plane.h"
#include "physicsobject.h"
#include "tquadtre.h"

class CollisionHandler : protected PhysicsObject
{
public:
    CollisionHandler();
    ~CollisionHandler();

    float GetDistance(PhysicsObject* obj0, PhysicsObject* obj1);
    void DetectCollision(std::vector<PhysicsObject*> pObjects);
    void Collide(PhysicsObject* object1, PhysicsObject* object2);
    void BallWallCollision(OctaBall* ball, Plane* wall);
    void BallBallCollision(OctaBall* ball0, OctaBall* ball1);

    int type() override;
};

#endif // COLLISIONHANDLER_H
