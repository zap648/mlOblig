#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
#include <string>
#include <vector>

enum class ComponentType // I'm faking reflection due to c++ doesn't let me :)
{
    Position,
    Health,
    Damage,
    Inventory
};

class Component
{

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

struct PositionComponent : virtual Component
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

struct HealthComponent : virtual Component
{
    std::vector<int> health;
};

struct DamageComponent : virtual Component
{
    std::vector<int> damage;
};

struct ItemComponent : virtual Component
{
    std::vector<std::string> item;
};

struct InventoryComponent : virtual Component
{
    std::vector<ItemComponent> inventory;
};

#endif // COMPONENTMANAGER_H
