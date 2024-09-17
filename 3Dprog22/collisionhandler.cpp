#include "collisionhandler.h"

CollisionHandler::CollisionHandler()
{

}

CollisionHandler::~CollisionHandler()
{

}

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
//                        mLogger->logText("Collision!");
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
