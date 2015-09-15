#include "AIControllerSystem.hpp"
#include "../World.hpp"
#include <Thor/Math/Random.hpp>

AIControllerSystem::AIControllerSystem()
{
    mFilter.requires(AIComponent::getId());
    mFilter.requires(TransformComponent::getId());
    mFilter.requires(MovementComponent::getId());
    mFilter.requires(HumanComponent::getId());
    mFilter.requires(FactionComponent::getId());
}

std::string AIControllerSystem::getId()
{
    return "AIControllerSystem";
}

void AIControllerSystem::update()
{
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        if (!mEntities[i]->getComponent<AIComponent>().hasTarget() && hasManager())
        {
            findTarget(mEntities[i]);
        }

        if (mEntities[i]->getComponent<AIComponent>().hasTarget())
        {
            bool hasWeapon = mEntities[i]->hasComponent<WeaponComponent>();
            handleMovement(mEntities[i], hasWeapon);
            if (hasWeapon)
            {
                handleAttack(mEntities[i]);
            }
        }
        else
        {
            handleNoTarget(mEntities[i]);
        }
    }
}

void AIControllerSystem::findTarget(es::Entity::Ptr e)
{
    es::EntityArray targetList;
    if (hasManager())
    {
        es::ComponentFilter targetFilter;
        targetFilter.requires(TransformComponent::getId());
        targetFilter.requires(FactionComponent::getId());
        targetFilter.requires(StatComponent::getId());
        targetList = mManager->getByFilter(targetFilter);
    }
    es::Entity::Ptr target = e->getComponent<AIComponent>().getTarget();
    sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition();
    float d = 999999.f;
    if (target != nullptr)
    {
        if (e->getComponent<AIComponent>().setTargetId(target->getId()))
        {
            d = thor::length(target->getComponent<TransformComponent>().getPosition() - ePos);
        }
    }
    for (std::size_t i = 0; i < targetList.size(); i++)
    {
        if (targetList[i] != nullptr)
        {
            float newD = thor::length(targetList[i]->getComponent<TransformComponent>().getPosition() - ePos);
            if (newD < d)
            {
                if (e->getComponent<AIComponent>().setTargetId(targetList[i]->getId()))
                {
                    d = newD;
                    target = targetList[i];
                }
            }
        }
    }
    if (target != nullptr)
    {
        e->getComponent<AIComponent>().setTargetId(target->getId());
    }
    else
    {
        e->getComponent<AIComponent>().setTargetId(0);
    }
}

void AIControllerSystem::handleMovement(es::Entity::Ptr e, bool hasWeapon)
{
    if (e->getComponent<AIComponent>().hasTarget())
    {
        sf::Vector2f tPos = e->getComponent<AIComponent>().getTarget()->getComponent<TransformComponent>().getPosition();
        sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition();
        sf::Vector2f diff = tPos - ePos;

        if (hasWeapon)
        {
            float dist = e->getComponent<WeaponComponent>().getRange() - 20.f;
            e->getComponent<HumanComponent>().setDirection(tPos);
            if (thor::length(diff) > dist)
            {
                e->getComponent<MovementComponent>().setDirection(diff);
            }
            else
            {
                e->getComponent<MovementComponent>().setDirection(sf::Vector2f());
            }
        }
        else
        {
            e->getComponent<MovementComponent>().setDirection(-diff);
            e->getComponent<HumanComponent>().setDirection(-tPos);
        }
    }
}

void AIControllerSystem::handleAttack(es::Entity::Ptr e)
{
    if (e->getComponent<AIComponent>().hasTarget() && e->hasComponent<WeaponComponent>())
    {
        WeaponComponent& w = e->getComponent<WeaponComponent>();
        es::Entity::Ptr target = e->getComponent<AIComponent>().getTarget();
        sf::Vector2f diff = target->getComponent<TransformComponent>().getPosition() - e->getComponent<TransformComponent>().getPosition();
        if (thor::length(diff) < w.getRange() && w.canAttack())
        {
            if (w.isLongRange())
            {
                w.attack(diff);
            }
            else
            {
                w.attack(target);
            }
        }
    }
}

void AIControllerSystem::handleNoTarget(es::Entity::Ptr e)
{
    if (e->hasComponent<HumanComponent>())
    {
        e->getComponent<HumanComponent>().setDirection(HumanComponent::Direction::S);
        e->getComponent<MovementComponent>().setDirection(sf::Vector2f());
        // TODO : Handle Boring
    }
}
