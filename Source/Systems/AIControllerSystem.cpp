#include "AIControllerSystem.hpp"
#include "../World.hpp"
#include <Thor/Math/Random.hpp>

AIControllerSystem::AIControllerSystem()
{
    mFilter.push_back(TransformComponent::getId());
    mFilter.push_back(SpriteComponent::getId());
    mFilter.push_back(CollisionComponent::getId());
    mFilter.push_back(MovementComponent::getId());
    mFilter.push_back(AIComponent::getId());
}

std::string AIControllerSystem::getId()
{
    return "AIControllerSystem";
}

void AIControllerSystem::update(sf::Time dt)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getComponent<LifeComponent>().isDead())
        {
            mManager->remove(mEntities[i]);
        }
        else // isAlive
        {
            if (!mEntities[i]->getComponent<AIComponent>().hasTarget() && mManager != nullptr)
            {
                findTarget(mEntities[i]);
            }

            if (mEntities[i]->getComponent<AIComponent>().hasTarget())
            {
                if (mEntities[i]->getComponent<AIComponent>().isFighter())
                {
                    handleGoToTarget(mEntities[i],dt);
                    handleAttack(mEntities[i]);
                }
                else
                {
                    handleEscapeTarget(mEntities[i],dt);
                }
            }
            else
            {
                handleNoTarget(mEntities[i],dt);
            }
        }
    }
}

void AIControllerSystem::findTarget(es::Entity::Ptr e)
{
    es::EntityArray targetList = mManager->getByFilter(AIComponent::getTargetFilter());
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

void AIControllerSystem::handleGoToTarget(es::Entity::Ptr e, sf::Time dt)
{
    if (e->getComponent<AIComponent>().hasTarget())
    {
        sf::Vector2f tPos = e->getComponent<AIComponent>().getTarget()->getComponent<TransformComponent>().getPosition();
        sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition();
        sf::Vector2f diff = tPos - ePos;
        sf::Vector2f mvt;

        float dist = 32.f;
        if (e->hasComponent<WeaponComponent>())
        {
            dist = e->getComponent<WeaponComponent>().getRange() - 16.f;
        }

        if (thor::length(diff) > dist)
        {
            mvt = thor::unitVector<float>(diff) * dt.asSeconds() * e->getComponent<MovementComponent>().getSpeed();
            if (World::instance().getEntities().getSystem<CollisionSystem>().handle(e,mvt))
            {
                e->getComponent<AIComponent>().setTarget(nullptr);
            }
        }

        // For Animation
        e->getComponent<MovementComponent>().update(dt,mvt,ePos,tPos);
    }
}

void AIControllerSystem::handleAttack(es::Entity::Ptr e)
{
    if (e->getComponent<AIComponent>().hasTarget() && e->getComponent<AIComponent>().isFighter() && e->hasComponent<WeaponComponent>())
    {
        WeaponComponent& w = e->getComponent<WeaponComponent>();
        es::Entity::Ptr target = e->getComponent<AIComponent>().getTarget();
        sf::Vector2f diff = e->getComponent<TransformComponent>().getPosition() - target->getComponent<TransformComponent>().getPosition();
        if (thor::length(diff) < w.getRange()
        && w.canAttack())
        {
            target->getComponent<LifeComponent>().inflige(w.getDamage());
            w.attack(diff);
        }
    }
}

void AIControllerSystem::handleEscapeTarget(es::Entity::Ptr e, sf::Time dt)
{
    if (e->getComponent<AIComponent>().hasTarget())
    {
        sf::Vector2f tPos = e->getComponent<AIComponent>().getTarget()->getComponent<TransformComponent>().getPosition();
        sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition();
        sf::Vector2f diff = tPos - ePos;
        sf::Vector2f mvt;

        if (thor::length(diff) > 0.f)
        {
            mvt = thor::unitVector<float>(-diff) * dt.asSeconds() * e->getComponent<MovementComponent>().getSpeed();

            if (World::instance().getEntities().getSystem<CollisionSystem>().handle(e,mvt))
            {
                e->getComponent<AIComponent>().setTarget(nullptr);
            }
        }

        // For Animation
        e->getComponent<MovementComponent>().update(dt,mvt,ePos,tPos - diff - diff);
    }
}

void AIControllerSystem::handleNoTarget(es::Entity::Ptr e, sf::Time dt)
{
    sf::Time bored = e->getComponent<AIComponent>().getBoredTime();

    if (bored > sf::seconds(3.f))
    {
        e->getComponent<AIComponent>().resetBoredTime();
        bored = sf::Time::Zero;
        e->getComponent<MovementComponent>().setDirection(static_cast<MovementComponent::Direction>(thor::random(0,3)));
        // TODO (#7#): Influence the direction to get them as near from the home as possible
    }

    sf::Vector2f mvt = sf::Vector2f(0.f,0.f);
    if (bored > sf::seconds(1.4f) && bored < sf::seconds(1.6f))
    {
        mvt = dt.asSeconds() * e->getComponent<MovementComponent>().getSpeed() * MovementComponent::getMovementFromDirection(e->getComponent<MovementComponent>().getDirection());
        World::instance().getEntities().getSystem<CollisionSystem>().handle(e,mvt);
    }

    e->getComponent<MovementComponent>().lastMovement(mvt,dt);
}
