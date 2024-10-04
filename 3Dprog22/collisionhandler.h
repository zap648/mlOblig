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
    // Quad-treet skulle være en todimensjonal std::vector som skulle styre
    // innen hvilken "grid" en ball eller vegg var i et visst tidspunkt
    // Da ville jeg ha endra DetectCollision til å melde i fra kollisjonen til objekta som er i ei rute (og rutene "rundt")
    // og bedre ytelsen til programet slik at det kan håndtere mange baller uten at det trenger å ødelegge ytelsen for mye

public:
    CollisionHandler();
    ~CollisionHandler();

    void addBall(OctaBall* ball);
    void addWall(Plane* wall);

//    void DetectBallWallCollision();
    void DetectCollision(std::vector<PhysicsObject*> pObjects);
    void Collide(PhysicsObject* object1, PhysicsObject* object2);
    void BallWallCollision(OctaBall* ball, Plane* wall);
    void BallBallCollision(OctaBall* ball0, OctaBall* ball1);

    int type() override;
};

#endif // COLLISIONHANDLER_H
