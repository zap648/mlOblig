#include "collisionhandler.h"
#include "logger.h"

CollisionHandler::CollisionHandler()
{

}

CollisionHandler::~CollisionHandler()
{

}

float CollisionHandler::GetDistance(PhysicsObject* obj0, PhysicsObject* obj1)
{
    if (obj0->type() != obj1->type())
    {
        if (obj1->type() == 0) // if the obj is wall
            return ((Plane *) obj1)->distanceFromPoint(obj0->getPosition());
        else // if the other obj is wall
            return ((Plane *) obj0)->distanceFromPoint(obj1->getPosition());
    }
    else // if the pObjects are equal (only both being balls matter)
        return obj0->getPosition().distanceToPoint(obj1->getPosition());
    // mLogger->logText(std::to_string(distance));
}

void CollisionHandler::DetectCollision(std::vector<PhysicsObject*> pObjects)
{
    if (pObjects.size() > 1)
    {
        std::vector<std::vector<int>> tracker;
        // assume the radius is 1
        for (int i = 0; pObjects.size() > i; i++)
        {
            tracker.push_back(*new std::vector<int>());
            for (int j = 0; j <= i; j++)
                tracker[i].push_back(j);

            for (int j = 0; pObjects.size() > j; j++)
            {
                if (std::find(tracker[i].begin(), tracker[i].end(), j) != tracker[i].end())
                {
                    continue;
                }
                float distance = GetDistance(pObjects[i], pObjects[j]);

                if (distance <= pObjects[i]->getRadius() + pObjects[j]->getRadius())
                {
                    Collide(pObjects[i], pObjects[j]);
                }
            }
        }
    }
    else
    {
        // pObjects is not bigger than 1
    }
}

void CollisionHandler::Collide(PhysicsObject* object1, PhysicsObject* object2)
{
//    mLogger->logText("Collision!");

    // object specific bounce (ball (1) or wall (0))
    // if one object is a ball (1) and the other is a wall (0)
    if ((object1->type() != object2->type()))
    {
        if (object1->type() == 0 && object2->type() == 1)
        {
            BallWallCollision((OctaBall *) object2, (Plane *) object1);
        }
        else
        {
            BallWallCollision((OctaBall *) object1, (Plane *) object2);
        }
    }
    // if both object are balls (1)
    else if ((object1->type() == 1 && object2->type() == 1))
    {
        BallBallCollision((OctaBall *) object1, (OctaBall *) object2);
    }
}

void CollisionHandler::BallWallCollision(OctaBall* ball, Plane* wall)
{
    // bounces the ball from the wall similar to light reflected from a mirror
    // Degrees on the collision vector gets reversered to be mirrored in comparisson to the normal
    ball->setVelocity(-2 * QVector3D().dotProduct(wall->getNormal(), ball->getVelocity()) * wall->getNormal() + ball->getVelocity());

    // Calculates the distance from the ball to the closest point on the plane
    float distance = wall->distanceFromPoint(ball->getPosition());
    // Push the ball out from the wall by the distance it went in to the wall
    ball->move(wall->getNormal() * (distance - ball->getRadius()));
}

void CollisionHandler::BallBallCollision(OctaBall* ball0, OctaBall* ball1)
{
    // Find the collision point
    QVector3D p1 = ball0->getPosition(); // ball0 current pos
    QVector3D vp = ball0->getVelocity(); // ball0 current speedVector
    QVector3D p0 = p1 - vp;              // ball0 previous pos (last frame)
    float mp = ball0->getMass();         // ball0 mass
    QVector3D q1 = ball1->getPosition(); // ball1 current poc
    QVector3D vq = ball1->getVelocity(); // ball1 current speedVector
    QVector3D q0 = q1 - vq;              // ball1 previous pos (last frame)
    float mq = ball1->getMass();         // ball1 mass

    QVector3D A = p1 - q1;
    QVector3D B = vq - vp;

    // Collision calculation
    float dist = A.length();

    // If the balls are departing from each other, cancel the function
    if (dist > (p0 - q0).length())
        return;

    QVector3D impactVector = p1 - q1;
    float mSum = mp + mq;

    // Push the balls from one another
    float overlap = dist - (ball0->getRadius() + ball1->getRadius());
    QVector3D dir = impactVector;
    dir = dir.normalized() * (overlap / 2);
    ball0->move(dir);
    ball1->move(-dir);

    // Fix the distance
    dist = A.length();
    impactVector = impactVector.normalized() * dist;

    // The common between the formulas
    float num = QVector3D().dotProduct(impactVector, B);
    float den = mSum * dist * dist;

    // Find velocity of ball0
    QVector3D deltaVA = impactVector;
    deltaVA *= 2 * mq * num / den;
    ball0->setVelocity(ball0->getVelocity() + deltaVA);

    // Find velocity of ball1
    QVector3D deltaVB = impactVector;
    deltaVB *= -2 * mp * num / den;
    ball1->setVelocity(ball1->getVelocity() + deltaVB);
}

int CollisionHandler::type()
{
    return -1;
}
