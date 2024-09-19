#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "octaball.h"
#include "plane.h"
#include "physicsobject.h"

class CollisionHandler : protected PhysicsObject
{
private:
    class Logger *mLogger;
    std::vector<OctaBall*> balls;
    std::vector<Plane*> walls;

public:
    CollisionHandler();
    ~CollisionHandler();

    void addBall(OctaBall* ball);
    void addWall(Plane* wall);

//    void DetectBallWallCollision();
    void DetectCollision(std::vector<PhysicsObject*> pObjects);
    void BallWallCollision(OctaBall* ball, Plane* wall);
};

#endif // COLLISIONHANDLER_H
