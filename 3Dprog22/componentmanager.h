#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
#include <string>
#include <vector>

template <class T>
class ComponentManager : T
{
private:
    std::map<int, T> components = new std::map<int, T>;
public:
    void AddComponent(int entityId, T component) { components[entityId] = component; }
    T GetComponent(int entityId) { return components[entityId]; }
    bool HasComponent(int entityId) { return components.count(entityId); }
    void RemoveComponent(int entityId) { components.erase(entityId); }
    std::map<int, T> GetAllComponents() { return components; }
};

class PositionComponent
{
public:
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> z;
    int size_;
};

class HealthComponent
{
public:
    std::vector<int> health;
    int size_;
};

class DamageComponent
{
public:
    std::vector<int> damage;
    int size_;
};

class InventoryComponent
{
public:
    std::vector<std::string> item; // I'm not actually sure what to put here... I'll figure it out later :)
    int size_;
};

#endif // COMPONENTMANAGER_H
