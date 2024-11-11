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

class DamageSystem : public ComponentSystem
{
    HealthComponent* healthComponent;
    DamageComponent* damageComponent;
    ComponentManager<HealthComponent>* healthManager;
    ComponentManager<DamageComponent>* damageManager;
public:
    DamageSystem(HealthComponent* healthComponent, DamageComponent* damageComponent, ComponentManager<HealthComponent>* healthManager, ComponentManager<DamageComponent>* damageManager)
    {
        this->healthComponent = healthComponent;
        this->damageComponent = damageComponent;
        this->healthManager = healthManager;
        this->damageManager = damageManager;
    }

    void Damage(const Entity* attacker, const Entity* receiver, float cooldown)
    {
        int attackerIndex = damageManager->GetComponent(attacker->Id);
        int receiverIndex = healthManager->GetComponent(receiver->Id);
        healthComponent->health[receiverIndex] -= damageComponent->damage[attackerIndex];
        damageComponent->cooldown[attackerIndex] = cooldown;
    }

    void Update(float deltaTime)
    {
        for (int i = 0; i < damageComponent->size; i++)
        {
            damageComponent->cooldown[i] -= deltaTime;
        }
    }
};

#endif // COMPONENTSYSTEM_H
