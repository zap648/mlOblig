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

class PositionComponent : virtual Component
{
public:
    // position axis
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> z;
    // direction axis
    std::vector<float> dx;
    std::vector<float> dy;
    std::vector<float> dz;
};

class HealthComponent : virtual Component
{
public:
    std::vector<int> health;
};

class DamageComponent : virtual Component
{
public:
    std::vector<int> damage;
};

class InventoryComponent : virtual Component
{
public:
    std::vector<std::string> item; // I'm not actually sure what to put here... I'll figure it out later :)
};

#endif // COMPONENTMANAGER_H
