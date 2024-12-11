#ifndef COMPONENTSYSTEM_H
#define COMPONENTSYSTEM_H


#include "component.h"
#include "entity.h"
#include <vector>

class ComponentSystem
{

};

class MovementSystem : public ComponentSystem
{
    PositionComponent* positionComponent;
    ComponentManager<PositionComponent>* positionManager;
public:
    MovementSystem(PositionComponent* posComponent, ComponentManager<PositionComponent>* posManager)
    {
        positionComponent = posComponent;
        positionManager = posManager;
    }

    void Update()
    {
        for (int i = 0; i < positionComponent->size; i++)
        {
            positionComponent->dx[i] += positionComponent->ax[i];
            positionComponent->dy[i] += positionComponent->ay[i];
            positionComponent->dz[i] += positionComponent->az[i];

            positionComponent->x[i] += positionComponent->dx[i];
            positionComponent->y[i] += positionComponent->dy[i];
            positionComponent->z[i] += positionComponent->dz[i];
        }
    }
};

class RenderSystem : public ComponentSystem
{
    RenderComponent* renderComponent;
    ComponentManager<RenderComponent>* renderManager;
public:
    RenderSystem(RenderComponent* renderComponent, ComponentManager<RenderComponent>* renderManager)
    {
        this->renderComponent = renderComponent;
        this->renderManager = renderManager;
    }

    void Init()
    {
        for (int i = 0; i < renderComponent->size; i++)
        {
            renderComponent->render[i]->init();
        }
    }

    void Move(const Entity* entity, float x, float y, float z)
    {
        int entityIndex = renderManager->GetComponent(entity->Id);
        renderComponent->render[entityIndex]->move(x, y, z);
    }

    void Update(const GLint mMatrixUniform)
    {
        for (int i = 0; i < renderComponent->size; i++)
        {
            renderComponent->render[i]->draw(mMatrixUniform);
        }
    }
};

class DamageSystem : public ComponentSystem
{
    HealthComponent* healthComponent;
    DamageComponent* damageComponent;
    ComponentManager<HealthComponent>* healthManager;
    ComponentManager<DamageComponent>* damageManager;
public:
    DamageSystem(HealthComponent* healthComponent, DamageComponent* damageComponent, ComponentManager<HealthComponent>* healthManager, ComponentManager<DamageComponent>* damageManager)
    {
        this->healthComponent = healthComponent;
        this->damageComponent = damageComponent;
        this->healthManager = healthManager;
        this->damageManager = damageManager;
    }

    void Damage(const Entity* attacker, const Entity* receiver, float cooldown)
    {
        int attackerIndex = damageManager->GetComponent(attacker->Id);
        int receiverIndex = healthManager->GetComponent(receiver->Id);
        healthComponent->health[receiverIndex] -= damageComponent->damage[attackerIndex];
        damageComponent->cooldown[attackerIndex] = cooldown;
    }

    void Update(float deltaTime)
    {
        for (int i = 0; i < damageComponent->size; i++)
        {
            damageComponent->cooldown[i] -= deltaTime;
        }
    }
};

class CollisionSystem : public ComponentSystem
{
    PositionComponent* positionComponent;
    PhysicsComponent* physicsComponent;
    ComponentManager<PositionComponent>* positionManager;
    ComponentManager<PhysicsComponent>* physicsManager;
public:
    CollisionSystem(PositionComponent* positionComponent, PhysicsComponent* physicsComponent, ComponentManager<PositionComponent>* positionManager, ComponentManager<PhysicsComponent>* physicsManager)
    {
        this->positionComponent = positionComponent;
        this->physicsComponent = physicsComponent;
        this->positionManager = positionManager;
        this->physicsManager = physicsManager;
    }

//    void Update()
//    {
//        if (pObjects.size() > 1)
//        {
//            std::vector<std::vector<int>> tracker;
//            // assume the radius is 1
//            for (int i = 0; pObjects.size() > i; i++)
//            {
//                tracker.push_back(*new std::vector<int>());
//                for (int j = 0; j <= i; j++)
//                    tracker[i].push_back(j);

//                for (int j = 0; pObjects.size() > j; j++)
//                {
//                    if (std::find(tracker[i].begin(), tracker[i].end(), j) != tracker[i].end())
//                    {
//                        continue;
//                    }
//                    float distance = GetDistance(pObjects[i], pObjects[j]);

//                    if (distance <= pObjects[i]->getRadius() + pObjects[j]->getRadius())
//                    {
//                        Collide(pObjects[i], pObjects[j]);
//                    }
//                }
//            }
//        }
//        else
//        {
//            // pObjects is not bigger than 1
//        }
//    }

//    void GetDistance()
//    {
//        if (obj0->type() != obj1->type())
//        {
//            if (obj1->type() == 0) // if the obj is wall
//                return ((Plane *) obj1)->distanceFromPoint(obj0->getPosition());
//            else // if the other obj is wall
//                return ((Plane *) obj0)->distanceFromPoint(obj1->getPosition());
//        }
//        else // if the pObjects are equal (only both being balls matter)
//            return obj0->getPosition().distanceToPoint(obj1->getPosition());
//        // mLogger->logText(std::to_string(distance));
//    }
};

#endif // COMPONENTSYSTEM_H
