#include "collisionhandler.h"

CollisionHandler::CollisionHandler()
{

}

CollisionHandler::~CollisionHandler()
{

}

void CollisionHandler::addBall(OctaBall* ball)
{
    balls.push_back(ball);
}

void CollisionHandler::addWall(Plane* wall)
{
    walls.push_back(wall);
}

//void CollisionHandler::DetectBallWallCollision()
//{
//    if (balls.size() > 0 && walls.size() > 0)
//    {
//        std::vector<std::vector<int>> tracker;
//        float distance;
//        for (int i = 0; balls.size() > i; i++)
//        {
//            tracker.push_back(*new std::vector<int>(i));
//            for (int j = 0; walls.size() > i; i++)
//            {
//                if (std::find(tracker[i].begin(), tracker[i].end(), j) != tracker[i].end() ||
//                    std::find(tracker[j].begin(), tracker[j].end(), i) != tracker[i].end())
//                {
//                    continue;
//                }
//                distance = balls[i]->getPosition().distanceToPoint(walls[j]->getPosition()) - balls[i]->getRadius();
////                mLogger->logText(std::to_string(distance));
//                if (distance <= 0)
//                {
//                    BallWallCollision(balls[i], walls[j]);
////                    mLogger->logText("Collision!");
//                }
//                tracker[i].push_back(j);
//            }
//        }
//    }
//}

void CollisionHandler::DetectCollision(std::vector<PhysicsObject*> pObjects)
{
//    mLogger->logText("Entered DetectCollision");
    float distance;
    if (pObjects.size() > 1)
    {
//        mLogger->logText("pObjects is " + std::to_string(pObjects.size()) + " units long");
        // assume the radius is 1
        for (int i = 0; pObjects.size() > i; i++)
        {
            for (int j = 0; pObjects.size() > j; j++)
            {
                if (i != j)
                {
                    distance = pObjects[i]->getPosition().distanceToPoint(pObjects[j]->getPosition());
//                    mLogger->logText(std::to_string(distance));
                    if (distance < 1)
                    {
                        pObjects[i]->setVelocity(-pObjects[i]->getVelocity());
                        pObjects[j]->setVelocity(-pObjects[j]->getVelocity());
                        mLogger->logText("Collision!");
                    }
                }
            }
        }
    }
    else
    {
//        mLogger->logText("pObjects is not larger than 1");
    }
//    mLogger->logText("Exited DetectCollision");
}

void CollisionHandler::BallWallCollision(OctaBall* ball, Plane* wall)
{
    QVector3D wallNormal = wall->getNormal();

    ball->setVelocity(ball->getVelocity() * wallNormal);
}
