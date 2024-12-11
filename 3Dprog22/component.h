#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "cube.h"

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
    // acceleration axis
    std::vector<float> ax;
    std::vector<float> ay;
    std::vector<float> az;

    PositionComponent() { size = 0; }

    void init()
    {
        for (int i = 0; i < size; i++)
        {
            x.push_back(0.0f); y.push_back(0.0f); z.push_back(0.0f);    // Position coordinates
            dx.push_back(0.0f); dy.push_back(0.0f); dz.push_back(0.0f); // Direction coordinates
            ax.push_back(0.0f); ay.push_back(0.0f); az.push_back(0.0f); // Acceleration coordinates
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

struct PhysicsComponent : Component
{
    std::vector<bool> b_physics;

    PhysicsComponent() { size = 0; }

    void init()
    {

    }
};

struct HealthComponent : Component
{
    std::vector<int> health;

    void init()
    {
        for (int i = 0; i < size; i++)
        {
            health.push_back(10);
        }
    }
};

struct DamageComponent : Component
{
    std::vector<int> damage;
    std::vector<float> cooldown;

    void init()
    {
        for (int i = 0; i < size; i++)
        {
            damage.push_back(1);
            cooldown.push_back(2.0f);
        }
    }
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
