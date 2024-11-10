#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "cube.h"

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
    int size;
};

template <class T>
class ComponentManager
{
    std::map<int, int> components;
public:
    void AddComponent(int entityId, T* component) { components.insert(std::make_pair(entityId, component->size)); component->size++; }
    int GetComponent(int entityId) { return components[entityId]; }
    bool HasComponent(int entityId) { return components.count(entityId); }
    void RemoveComponent(int entityId) { components.erase(entityId); }
    std::map<int, int> GetAllComponents() { return components; }
};

struct PositionComponent : public Component
{
    // position axis
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> z;
    // direction axis
    std::vector<float> dx;
    std::vector<float> dy;
    std::vector<float> dz;

    PositionComponent() { size = 0; }

    void init()
    {
        for (int i = 0; i < size; i++)
        {
            x.push_back(0.0f); y.push_back(0.0f); z.push_back(0.0f);    // Position coordinates
            dx.push_back(0.0f); dy.push_back(0.0f); dz.push_back(0.0f); // Direction coordinates
        }
    }
};

struct RenderComponent : Component
{
    std::vector<VisualObject*> render;

    RenderComponent() { size = 0; }

    void init()
    {
        for (int i = 0; i < size; i++)
        {
            render.push_back(new Cube(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
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
