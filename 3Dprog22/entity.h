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
                            HealthComponent& hpComp, ComponentManager& compManager)
    {
        entity.m_componentMask.insert(ComponentType::Health);
        hpComp.health.push_back(hp);
        compManager.components[entity.Id] = hpComp.health.size() - 1;
    }

    void AddDamageComponent(Entity& entity,
                            int dmg, float cooldwn,
                            DamageComponent& dmgComp, ComponentManager& compManager)
    {
        entity.m_componentMask.insert(ComponentType::Damage);
        dmgComp.damage.push_back(dmg);
        dmgComp.cooldown.push_back(cooldwn);
        compManager.components[entity.Id] = dmgComp.damage.size() - 1;
    }

    void AddInventoryComponent(Entity& entity,
                               ItemComponent& itemComp,
                               InventoryComponent& invComp, ComponentManager& compManager)
    {
        entity.m_componentMask.insert(ComponentType::Inventory);
        invComp.inventory.push_back(itemComp);
        compManager.components[entity.Id] = invComp.inventory.size() - 1;
    }

    void AddItemComponent(Entity& entity,
                          std::string& item,
                          ItemComponent& itemComp, ComponentManager& compManager)
    {
        entity.m_componentMask.insert(ComponentType::Item);
        itemComp.item.push_back(item);
        compManager.components[entity.Id] = itemComp.item.size() - 1;
    }
};

#endif // ENTITY_H
