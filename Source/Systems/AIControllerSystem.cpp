#include "AIControllerSystem.hpp"
#include "../World.hpp"
#include <Thor/Math/Random.hpp>

AIControllerSystem::AIControllerSystem()
{
    mFilter.push_back(TransformComponent::getId());
    mFilter.push_back(SpriteComponent::getId());
    mFilter.push_back(BoxComponent::getId());
    mFilter.push_back(CollisionComponent::getId());
    mFilter.push_back(MovementComponent::getId());
    mFilter.push_back(AnimationComponent::getId());
    mFilter.push_back(AIComponent::getId());
}

std::string AIControllerSystem::getId()
{
    return "AIControllerSystem";
}

void AIControllerSystem::update()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (!mEntities[i]->getComponent<AIComponent>().hasTarget() && hasManager())
        {
            findTarget(mEntities[i]);
        }

        if (mEntities[i]->getComponent<AIComponent>().hasTarget())
        {
            if (mEntities[i]->hasComponent<WeaponComponent>())
            {
                handleGoToTarget(mEntities[i]);
                handleAttack(mEntities[i]);
            }
            else
            {
                handleEscapeTarget(mEntities[i]);
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
        targetFilter.push_back(TransformComponent::getId());
        targetFilter.push_back(SpriteComponent::getId());
        targetFilter.push_back(LifeComponent::getId());
        targetList = mManager->getByFilter(targetFilter);
    }
    es::Entity::Ptr target = e->getComponent<AIComponent>().getTarget();
    sf::Vector2f tPos, ePos = e->getComponent<TransformComponent>().getPosition();
    for (unsigned int i = 0; i < targetList.size(); i++)
    {
        if (targetList[i] != nullptr)
        {
            sf::Vector2f tePos = targetList[i]->getComponent<TransformComponent>().getPosition();
            if (targetList[i]->getId() != e->getId()
            && targetList[i]->getComponent<LifeComponent>().isAlive()
            && thor::length(ePos - tePos) < e->getComponent<AIComponent>().getViewDistance())
            {
                if (targetList[i]->hasComponent<MonsterComponent>() != e->hasComponent<MonsterComponent>())
                {
                    if (target == nullptr)
                    {
                        target = targetList[i];
                    }
                    else if (thor::length(ePos - tePos) < thor::length(ePos - tPos))
                    {
                        target = targetList[i];
                    }
                }
            }
        }
        if (target != nullptr)
        {
            tPos = target->getComponent<TransformComponent>().getPosition();
        }
    }
    e->getComponent<AIComponent>().setTarget(target);
}

void AIControllerSystem::handleGoToTarget(es::Entity::Ptr e)
{
    if (e->getComponent<AIComponent>().hasTarget())
    {
        sf::Vector2f tPos = e->getComponent<AIComponent>().getTarget()->getComponent<TransformComponent>().getPosition();
        sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition();
        sf::Vector2f diff = tPos - ePos;

        e->getComponent<AnimationComponent>().setDirection(tPos);

        float dist = 32.f;
        if (e->hasComponent<WeaponComponent>())
        {
            dist = e->getComponent<WeaponComponent>().getRange() - 16.f;
        }

        if (thor::length(diff) > dist)
        {
            e->getComponent<MovementComponent>().setDirection(diff);
        }
        else
        {
            e->getComponent<MovementComponent>().setDirection(sf::Vector2f());
        }
    }
}

void AIControllerSystem::handleAttack(es::Entity::Ptr e)
{
    // TODO : Fix it
    /*if (e->getComponent<AIComponent>().hasTarget() && e->hasComponent<WeaponComponent>())
    {
        WeaponComponent& w = e->getComponent<WeaponComponent>();
        es::Entity::Ptr target = e->getComponent<AIComponent>().getTarget();
        sf::Vector2f diff = e->getComponent<TransformComponent>().getPosition() - target->getComponent<TransformComponent>().getPosition();
        if (thor::length(diff) < w.getRange() && w.canAttack())
        {
            target->getComponent<LifeComponent>().inflige(w.getDamage());
            w.attack(diff);
        }
    }
    */
}

void AIControllerSystem::handleEscapeTarget(es::Entity::Ptr e)
{
    if (e->getComponent<AIComponent>().hasTarget())
    {
        // TODO : Escape
    }
}

void AIControllerSystem::handleNoTarget(es::Entity::Ptr e)
{
    if (e->hasComponent<AnimationComponent>())
    {
        e->getComponent<AnimationComponent>().setDirection(AnimationComponent::Direction::S);
        // TODO : Handle Boring
    }
}
