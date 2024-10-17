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
    void AddPositionComponent(
            Entity& entity,
            float X,
            float Y,
            float Z,
            PositionComponent& posComp,
            ComponentManager& compManager)
    {
        entity.m_componentMask.insert(ComponentType::PositionComponent);
        posComp.x.push_back(X);
        posComp.y.push_back(Y);
        posComp.z.push_back(Z);
        compManager.components[entity.Id] = posComp.x.size() - 1;
    }
};

#endif // ENTITY_H
