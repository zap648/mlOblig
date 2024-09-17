#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "physicsobject.h"

class CollisionHandler : PhysicsObject
{
public:
    CollisionHandler();
    ~CollisionHandler();

    void DetectCollision(std::vector<PhysicsObject*> pObjects);
};

#endif // COLLISIONHANDLER_H
