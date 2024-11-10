#ifndef COMPONENTSYSTEM_H
#define COMPONENTSYSTEM_H


#include "component.h"
#include "entity.h"
#include <vector>

class ComponentSystem
{

};

class MovementSystem : public ComponentSystem
{
    PositionComponent* positionComponent;
    ComponentManager<PositionComponent>* positionManager;
public:
    MovementSystem(PositionComponent* posComponent, ComponentManager<PositionComponent>* posManager)
    {
        positionComponent = posComponent;
        positionManager = posManager;
    }

    void Update()
    {
        for (int i = 0; i < positionComponent->size; i++)
        {
            positionComponent->x[i] += positionComponent->dx[i];
            positionComponent->y[i] += positionComponent->dy[i];
            positionComponent->z[i] += positionComponent->dz[i];
        }
    }
};

#endif // COMPONENTSYSTEM_H
