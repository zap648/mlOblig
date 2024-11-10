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

class RenderSystem : public ComponentSystem
{
    RenderComponent* renderComponent;
    ComponentManager<RenderComponent>* renderManager;
public:
    RenderSystem(RenderComponent* renderComponent, ComponentManager<RenderComponent>* renderManager)
    {
        this->renderComponent = renderComponent;
        this->renderManager = renderManager;
    }

    void Init()
    {
        for (int i = 0; i < renderComponent->size; i++)
        {
            renderComponent->render[i]->init();
        }
    }

    void Move(const Entity* entity, float x, float y, float z)
    {
        int entityIndex = renderManager->GetComponent(entity->Id);
        renderComponent->render[entityIndex]->move(x, y, z);
    }

    void Update(const GLint mMatrixUniform)
    {
        for (int i = 0; i < renderComponent->size; i++)
        {
            renderComponent->render[i]->draw(mMatrixUniform);
        }
    }
};

#endif // COMPONENTSYSTEM_H
