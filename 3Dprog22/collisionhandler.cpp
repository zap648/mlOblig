#include "collisionhandler.h"

CollisionHandler::CollisionHandler()
{
    //Get the instance of the utility Output logger
    //Have to do this, else program will crash (or you have to put in nullptr tests...)
    mLogger = Logger::getInstance();
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
    if (pObjects.size() > 1)
    {
        std::vector<std::vector<int>> tracker;
//        mLogger->logText("mPhysics is " + std::to_string(pObjects.size()) + " units long");
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
                float distance = pObjects[i]->getPosition().distanceToPoint(pObjects[j]->getPosition());
//                mLogger->logText(std::to_string(distance));
                if (distance < pObjects[i]->getRadius())
                {
                    Collide(pObjects[i], pObjects[j]);
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

void CollisionHandler::Collide(PhysicsObject* object1, PhysicsObject* object2)
{
    // Collide-funksjonen må endre seg til å kunne regne ut avstanden fra ballen til det nærmeste punktet på planet
//    mLogger->logText("Collision!");
    object1->setVelocity(object1->getVelocity() * -1);
    object2->setVelocity(object2->getVelocity() * -1);

    // objektspecifike sprett (ball (1) or wall (0))
    // viss et objekt er ball (1) og den andre er en vegg (0)
    if ((object1->type() == 0 && object2->type() == 1) ||
            (object2->type() == 0 && object1->type() == 0))
    {
        if (object1->type() == 0 && object2->type() == 1)
        {
            // Ville ha likt og testa om denne Casten funker
            BallWallCollision((OctaBall *) object2->type(), (Plane *) object1->type());
        }
        else
        {
            BallWallCollision((OctaBall *) object1->type(), (Plane *) object2->type());
        }
    }
    else if ((object1->type() == 1 && object2->type() == 1))
    {
        BallBallCollision((OctaBall *) object1, (OctaBall *) object2);
    }
    if (type() == 1)
    {
        // ballsprettefunksjon hit
    }
//    mLogger->logText("New velocity is " + std::to_string(object1->getVelocity().y()) + " and " + std::to_string(object2->getVelocity().y()));
}

void CollisionHandler::BallWallCollision(OctaBall* ball, Plane* wall)
{
    QVector3D wallNormal = wall->getNormal();

    // Ballen får normalen til planet og går oppover like langt som den gikk ned i planet
    // Eks: Viss ballen gikk -0.3 enheter under planet, skal ballen nå være 0.3 enheter over planet, i retning mot normalen
    // x og y retning (i forhold til normalen) skal være den samme

    // Uferdig, ballen skal etter kolisjon endre hastighetvektoren til å gå fra veggen, men uten å endre x,z retningene (i forhold til normalen)
//    ball->setVelocity(ball->getVelocity() * wallNormal); // Vil sannsynligvis ikke virke
}

void CollisionHandler::BallBallCollision(OctaBall* ball0, OctaBall* ball1)
{
    // Likt som i BallWallCollision, skal ballene vekk fra ballen like langt som de gikk inn i hverandre
    // "Normalen" i dette tilfellet vil være fra ballen sitt senter til den andre ballen (.normalized())
    // da de støtte på hverandre, slik at kollisjonen er litt mer dynamisk enn med en vegg

    // Ballen skal også skifte hastighetvektor til å fortsete i retning fra kollisjonspunktet.
    // Jeg følger formlene som blir vist i 9.7.5 (hvor n er normalen funnet i forrige kommentar og d som er avstanden mellom ballene da de kolliderte)
    // og endrer hastighetsvektoren til summen
}
