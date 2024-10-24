#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "visualobject.h"

enum class ComponentType // I'm faking reflection due to c++ not letting me :)
{
    Position,
    Health,
    Damage,
    Inventory,
    Item,
    Render,
    Controller
};

class ComponentManager
{
public:
    std::map<int, int> components;

    void AddComponent(int entityId, int component) { components[entityId] = component; }
    auto GetComponent(int entityId) { return components[entityId]; }
    bool HasComponent(int entityId) { return components.count(entityId); }
    void RemoveComponent(int entityId) { components.erase(entityId); }
    std::map<int, int> GetAllComponents() { return components; }
};

struct PositionComponent
{
    // position axis
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> z;
    // direction axis
    std::vector<float> dx;
    std::vector<float> dy;
    std::vector<float> dz;

    int size;
};

struct HealthComponent
{
    std::vector<int> health;

    int size;
};

struct DamageComponent
{
    std::vector<int> damage;
    std::vector<float> cooldown;

    int size;
};

struct ItemComponent
{
    std::vector<std::string> item;

    int size;
};

struct InventoryComponent
{
    std::vector<ItemComponent> inventory;

    int size;
};

struct RenderComponent
{
    std::vector<VisualObject*> render;

    int size;
};

struct ControllerComponent
{
    std::vector<bool> moveUp{false};
    std::vector<bool> moveDown{false};
    std::vector<bool> moveLeft{false};
    std::vector<bool> moveRight{false};
    std::vector<bool> moveFor{false};
    std::vector<bool> moveBack{false};
    std::vector<bool> attack{false};

    int size;
};

#endif // COMPONENTMANAGER_H
