#ifndef COMPONENTSYSTEM_H
#define COMPONENTSYSTEM_H


#include "component.h"
#include "entity.h"
#include <vector>
class ComponentSystem
{
public:
    virtual void Update(Entity entity);
};

class MovementSystem : ComponentSystem
{
private:
    std::vector<int> positionIds;
public:
    void AddEntity(const Entity &entity, const ComponentManager& componentManager)
    {

    }
    void RemoveEntity(int entityId, const ComponentManager& componentManager);
    void Update(PositionComponent &positions)
    {
        for (int i = 0; i < positionIds.size(); i++)
        {
            int positionIndex = positionIds[i];
            positions.x[positionIndex] += 0.01f;
            positions.y[positionIndex] += 0.0f;
            positions.z[positionIndex] += 0.0f;
        }
    }
};

class DamageSystem : ComponentSystem
{

};

#endif // COMPONENTSYSTEM_H
