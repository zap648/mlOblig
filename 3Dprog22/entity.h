#ifndef ENTITY_H
#define ENTITY_H

// A basic entity with an integer identification - int Id;
#include <map>
#include <unordered_set>
#include "component.h"

static int idCount = 0;

class Entity
{
public:
    std::unordered_set<ComponentType> m_componentMask;  // This, is a bucket. ("Dear God!")
    int Id;                                             // There's more.      ("Nooooo...")

    Entity()
    {
        Id = idCount++;
    }
};

class EntityBuilder
{
public:
    void AddPositionComponent(Entity& entity,
            float X, float Y, float Z,
            PositionComponent& posComp, ComponentManager& compManager)
    {
        entity.m_componentMask.insert(ComponentType::Position);
        // place starting coordinates in position component
        posComp.x.push_back(X); posComp.y.push_back(Y); posComp.z.push_back(Z);
        posComp.dx.push_back(0.0f); posComp.dy.push_back(0.0f); posComp.dz.push_back(0.0f);
        compManager.components[entity.Id] = posComp.x.size() - 1;
    }

    void AddHealthComponent(Entity& entity,
                            int hp,
                            HealthComponent& healthComp, ComponentManager& compManager)
    {
        entity.m_componentMask.insert(ComponentType::Health);
        healthComp.health.push_back(hp);
        compManager.components[entity.Id] = healthComp.health.size() - 1;
    }
};

#endif // ENTITY_H
