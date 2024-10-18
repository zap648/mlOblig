#ifndef COMPONENTSYSTEM_H
#define COMPONENTSYSTEM_H


#include "component.h"
#include "entity.h"
#include <vector>
class ComponentSystem
{
//public:
//    virtual void Update(Entity entity);
};

class MovementSystem : ComponentSystem
{
private:
    std::vector<int> positionIndices;
public:
    void AddEntity(const Entity &entity, const ComponentManager& componentManager)
    {
        positionIndices.push_back(componentManager.components.at(entity.Id));
    }
    void RemoveEntity(int entityId, const ComponentManager& componentManager)
    {
        // Uhhh... I don't necissarily *need* to do this (yet) :)
    }
    void Update(PositionComponent &positions)
    {
        for (int i = 0; i < positionIndices.size(); i++)
        {
            int positionIndex = positionIndices[i];
            positions.x[positionIndex] += positions.dx[positionIndex];
            positions.y[positionIndex] += positions.dy[positionIndex];
            positions.z[positionIndex] += positions.dz[positionIndex];
        }
    }
};

class DamageSystem : ComponentSystem
{

};

#endif // COMPONENTSYSTEM_H
