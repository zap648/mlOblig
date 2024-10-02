#include "collisionhandler.h"
#include "logger.h"

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
                float distance = 0;
                if (pObjects[i]->type() != pObjects[j]->type())
                {
                    if (pObjects[j]->type() == 0) // if the pObjects is wall
                        distance = ((Plane *) pObjects[j])->distanceFromPoint(pObjects[i]->getPosition());
                    else // if the other pObjects is wall
                        distance = ((Plane *) pObjects[i])->distanceFromPoint(pObjects[j]->getPosition());
                }
                else // if the pObjects are equal (only both being balls matter)
                    distance = pObjects[i]->getPosition().distanceToPoint(pObjects[j]->getPosition());
                // mLogger->logText(std::to_string(distance));

                if (distance <= pObjects[i]->getRadius() + pObjects[j]->getRadius())
                {
                    Collide(pObjects[i], pObjects[j]);
                }
            }
        }
    }
    else
    {
        // pObjects er ikke større en 1
    }
}

void CollisionHandler::Collide(PhysicsObject* object1, PhysicsObject* object2)
{
//    mLogger->logText("Collision!");

    // objektspesifike sprett (ball (1) or wall (0))
    // viss et objekt er ball (1) og den andre er en vegg (0)
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
    // viss begge objekta er baller (1)
    else if ((object1->type() == 1 && object2->type() == 1))
    {
        BallBallCollision((OctaBall *) object1, (OctaBall *) object2);
    }
}

void CollisionHandler::BallWallCollision(OctaBall* ball, Plane* wall)
{
    // Spretter ballen vekk fra ballen på samme måte som lys reflekteres fra speil
    // Grader på inngangsvektoren blir reversert til å bli speilvendt i forhold til normalen
    ball->setVelocity(-2 * QVector3D().dotProduct(wall->getNormal(), ball->getVelocity()) * wall->getNormal() + ball->getVelocity());

    // Regner ut avstanden fra ballen til det nærmeste punktet på planet
    float distance = wall->distanceFromPoint(ball->getPosition());
    // Dytter ballen ut fra veggen like mye som han gikk inn i veggen
    ball->move(wall->getNormal() * (distance - ball->getRadius()));
}

void CollisionHandler::BallBallCollision(OctaBall* ball0, OctaBall* ball1)
{
    //    mLogger->logText("Collision!");

    // Finn kollisjonspunktet
    QVector3D p1 = ball0->getPosition(); // ball0 current pos
    QVector3D vp = ball0->getVelocity(); // ball0 current speedVector
    QVector3D p0 = p1 - vp;              // ball0 previous pos (last frame)
    QVector3D q1 = ball1->getPosition(); // ball1 current poc
    QVector3D vq = ball1->getVelocity(); // ball1 current speedVector
    QVector3D q0 = q1 - vq;              // ball1 previous pos (last frame)

    QVector3D A = p0 - q0;
    QVector3D B = vp - vq;

    float rp = ball0->getRadius();
    float rq = ball1->getRadius();
    float t = -( QVector3D().dotProduct(A, B) )
                - std::sqrt(
                    std::pow(QVector3D().dotProduct(A, B), 2)
                    - QVector3D().dotProduct(B, B) * ( QVector3D().dotProduct(A, A) - std::pow((rp + rq), 2) )
                )
            / QVector3D().dotProduct(B, B);
//    float t2 = (-(QVector3D().dotProduct(A, B)))
//            + std::sqrt(
//                std::pow(QVector3D().dotProduct(A, B), 2)
//                - QVector3D().dotProduct(B, B)
//                * (QVector3D().dotProduct(A, A) - std::pow((rp + rq), 2))
//                )
//            / QVector3D().dotProduct(B, B);
//    float t = QVector3D().dotProduct(A, B) / QVector3D().dotProduct(B, B);
    QVector3D Pt = p0 + (t * vp);
    QVector3D Qt = q0 + (t * vq);

    QVector3D N = (Qt - Pt).normalized();
    // OBS! Finn ut kollisjonspunktet til ballene før du finner ut d!
//    float d = std::sqrt(QVector3D().dotProduct(A, A)) + 2*t*QVector3D().dotProduct(A, B) + std::pow(t, 2)*QVector3D().dotProduct(B, B);
    QVector3D d = Qt - Pt;
//    float v0

    //    mLogger->logText("New velocity is " + std::to_string(object1->getVelocity().y()) + " and " + std::to_string(object2->getVelocity().y()));

//    ball0->setVelocity(vp*N + vp*d);    // Ball-sprettefunksjonen fungerer ikke
//    ball1->setVelocity(vq*N - vq*d);
    ball0->setVelocity(-2 * QVector3D().dotProduct(N, vp) * N + vp); // Men vegg-sprettefunksjonen "fungerer"
    ball1->setVelocity(-2 * QVector3D().dotProduct(N, vq) * N + vq);
}

int CollisionHandler::type()
{
    return -1;
}
