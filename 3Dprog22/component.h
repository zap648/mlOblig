#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "visualobject.h"

enum class ComponentType // I'm faking reflection due to c++ not letting me :)
{
    Position,   // 0 - Position
    Health,     // 1 - Health
    Damage,     // 2 - Damage
    Inventory,  // 3 - Inventory
    Item,       // 4 - Item
    Render,     // 5 - Render
    Controller  // 6 - Controller
};

struct Component
{
    ComponentType type;
    int size;
};

struct ComponentManager
{
    std::map<int, int> components;

    void AddComponent(int entityId, int componentIndex) { components[entityId] = componentIndex; }
    int GetComponent(int entityId) { return components[entityId]; }        // Returns the component index (where the entity is in the component array) of the entity
    bool HasComponent(int entityId) { return components.count(entityId); }  // Returns bool if the entity has the component (0 - false, 1++ - true)
    void RemoveComponent(int entityId) { components.erase(entityId); }      // Removes components of entity from the map
    std::map<int, int> GetAllComponents() { return components; }            // Returns entity component map
};

struct PositionComponent : Component
{
    // position axis
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> z;
    // direction axis
    std::vector<float> dx;
    std::vector<float> dy;
    std::vector<float> dz;
};

struct HealthComponent : Component
{
    std::vector<int> health;
};

struct DamageComponent : Component
{
    std::vector<int> damage;
    std::vector<float> cooldown;
};

struct ItemComponent : Component
{
    std::vector<std::string> item;
};

struct InventoryComponent : Component
{
    std::vector<ItemComponent> inventory;
};

struct RenderComponent : Component
{
    std::vector<VisualObject*> render;
};

struct ControllerComponent : Component
{
    std::vector<bool> moveUp{false};
    std::vector<bool> moveDown{false};
    std::vector<bool> moveLeft{false};
    std::vector<bool> moveRight{false};
    std::vector<bool> moveFor{false};
    std::vector<bool> moveBack{false};
    std::vector<bool> attack{false};
};

#endif // COMPONENTMANAGER_H
