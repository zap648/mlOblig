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
    std::unordered_set<ComponentType> b_componentType;  // This, is a bucket. ("Dear God!")
    int Id;                                             // There's more.      ("Nooooo...")

    Entity()
    {
        Id = idCount++;
    }
    Entity(int x)
    {
        Id = x;
    }
};

class EntityBuilder
{
public:
    void AddPositionComponent(Entity& entity,
                              float x, float y, float z,
                              PositionComponent& posComp, ComponentManager& compManager)
    {
        entity.b_componentType.insert(ComponentType::Position);
        // place starting coordinates in position component
        posComp.x.push_back(x); posComp.y.push_back(y); posComp.z.push_back(z);
        posComp.dx.push_back(0.0f); posComp.dy.push_back(0.0f); posComp.dz.push_back(0.0f);
        compManager.components[entity.Id] = posComp.size;
        posComp.size++;
    }

    void AddHealthComponent(Entity& entity,
                            int hp,
                            HealthComponent& hpComp, ComponentManager& compManager)
    {
        entity.b_componentType.insert(ComponentType::Health);
        hpComp.health.push_back(hp);
        compManager.components[entity.Id] = hpComp.size;
        hpComp.size++;
    }

    void AddDamageComponent(Entity& entity,
                            int dmg, float cool,
                            DamageComponent& dmgComp, ComponentManager& compManager)
    {
        entity.b_componentType.insert(ComponentType::Damage);
        dmgComp.damage.push_back(dmg);
        dmgComp.cooldown.push_back(cool);
        compManager.components[entity.Id] = dmgComp.size;
        dmgComp.size++;
    }

    void AddInventoryComponent(Entity& entity,
                               ItemComponent& itemComp,
                               InventoryComponent& invComp, ComponentManager& compManager)
    {
        entity.b_componentType.insert(ComponentType::Inventory);
        invComp.inventory.push_back(itemComp);
        compManager.components[entity.Id] = invComp.size;
        invComp.size++;
    }

    void AddItemComponent(Entity& entity,
                          std::string& item,
                          ItemComponent& itemComp, ComponentManager& compManager)
    {
        entity.b_componentType.insert(ComponentType::Item);
        itemComp.item.push_back(item);
        compManager.components[entity.Id] = itemComp.size;
        itemComp.size++;
    }

    void AddRenderComponent(Entity& entity,
                            VisualObject& render,
                            RenderComponent& rendComp, ComponentManager& compManager)
    {
        entity.b_componentType.insert(ComponentType::Render);
        rendComp.render.push_back(&render);
        compManager.components[entity.Id] = rendComp.size;
        rendComp.size++;
    }

    void AddControllerComponent(Entity& entity, ControllerComponent& contComp, ComponentManager& compManager)
    {
        entity.b_componentType.insert(ComponentType::Controller);
        contComp.moveUp.push_back(false);
        contComp.moveDown.push_back(false);
        contComp.moveLeft.push_back(false);
        contComp.moveRight.push_back(false);
        contComp.moveFor.push_back(false);
        contComp.moveBack.push_back(false);
        contComp.attack.push_back(false);
        compManager.components[entity.Id] = contComp.size;
        contComp.size++;
    }
};

#endif // ENTITY_H
