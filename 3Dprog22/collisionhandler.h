#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "octaball.h"
#include "plane.h"
#include "physicsobject.h"
#include "tquadtre.h"

class CollisionHandler : protected PhysicsObject
{
private:
    // Disse er egentlig ubruklige (sammen med DetectBallWallCollision() siden DetectCollision() gjør jobben greit
    std::vector<OctaBall*> balls;
    std::vector<Plane*> walls;

    QuadTre<std::string, PhysicsObject> mQuadTre;

public:
    CollisionHandler();
    ~CollisionHandler();

    void addBall(OctaBall* ball);
    void addWall(Plane* wall);
    void addPhysics(std::vector<PhysicsObject*> objects);

//    void DetectBallWallCollision();
    void DetectCollision(std::vector<PhysicsObject*> pObjects);
    void Collide(PhysicsObject* object1, PhysicsObject* object2);
    void BallWallCollision(OctaBall* ball, Plane* wall);
    void BallBallCollision(OctaBall* ball0, OctaBall* ball1);

    int type() override;
};

#endif // COLLISIONHANDLER_H
