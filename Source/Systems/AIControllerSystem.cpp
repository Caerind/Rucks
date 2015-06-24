#include "AIControllerSystem.hpp"

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
            if (mEntities[i]->getComponent<AIComponent>().isMonster())
            {
                handleMonster(mEntities[i],dt);
                handleAttack(mEntities[i]);
            }
            else
            {
                if (mEntities[i]->getComponent<AIComponent>().isFighter())
                {
                    handleFighter(mEntities[i],dt);
                    handleAttack(mEntities[i]);
                }
                else
                {
                    handlePacific(mEntities[i],dt);
                }
            }
        }
    }
}

void AIControllerSystem::handleMonster(es::Entity::Ptr e, sf::Time dt)
{
    AIComponent& a = e->getComponent<AIComponent>();
    MovementComponent& m = e->getComponent<MovementComponent>();
    sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition();

    if (!a.hasTarget() && mManager != nullptr)
    {
        es::EntityManager::EntityArray targetList = mManager->getByFilter(AIComponent::getTargetFilter());
        es::Entity::Ptr target = nullptr;
        sf::Vector2f tPos;
        for (unsigned int i = 0; i < targetList.size(); i++)
        {
            if (targetList[i] != nullptr)
            {
                sf::Vector2f tePos = targetList[i]->getComponent<TransformComponent>().getPosition();
                if (targetList[i]->getId() != e->getId()
                && targetList[i]->getComponent<LifeComponent>().isAlive()
                && thor::length(ePos - tePos)
                < a.getViewDistance())
                {
                    if (targetList[i]->hasComponent<AIComponent>())
                    {
                        if (!targetList[i]->getComponent<AIComponent>().isMonster())
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
                    else
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
        a.setTarget(target);
    }
    if (a.hasTarget())
    {
        sf::Vector2f diff = a.getTarget()->getComponent<TransformComponent>().getPosition() - ePos;
        sf::Vector2f mvt;
        if (thor::length(diff) > e->getComponent<WeaponComponent>().getRange() - 16.f)
        {
            mvt = thor::unitVector<float>(diff) * dt.asSeconds() * m.getSpeed();
            CollisionComponent& c = e->getComponent<CollisionComponent>();
            c.setCenter(ePos + mvt);
            if (collision(c.getCollisionBox(), mvt, e->getId()))
            {
                a.setTarget(nullptr);
            }
            e->getComponent<TransformComponent>().move(mvt);
            c.setCenter(e->getComponent<TransformComponent>().getPosition());
        }

        // For Animation
        if (mvt != sf::Vector2f(0.f,0.f))
        {
            e->getComponent<MovementComponent>().walking(dt);
        }
        else
        {
            e->getComponent<MovementComponent>().stopWalking();
        }
    }
    else
    {
        e->getComponent<MovementComponent>().stopWalking();
        // TODO (#3#): Lambda Movement
    }
}

void AIControllerSystem::handleFighter(es::Entity::Ptr e, sf::Time dt)
{
    AIComponent& a = e->getComponent<AIComponent>();
    MovementComponent& m = e->getComponent<MovementComponent>();
    sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition();

    if (!a.hasTarget() && mManager != nullptr)
    {
        es::EntityManager::EntityArray targetList = mManager->getByFilter(AIComponent::getTargetFilter());
        es::Entity::Ptr target = nullptr;
        sf::Vector2f tPos;
        for (unsigned int i = 0; i < targetList.size(); i++)
        {
            if (targetList[i] != nullptr)
            {
                sf::Vector2f tePos = targetList[i]->getComponent<TransformComponent>().getPosition();
                if (targetList[i]->getId() != e->getId()
                && targetList[i]->getComponent<LifeComponent>().isAlive()
                && thor::length(ePos - tePos)
                < a.getViewDistance())
                {
                    if (targetList[i]->hasComponent<AIComponent>())
                    {
                        if (targetList[i]->getComponent<AIComponent>().isMonster())
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
            }
            if (target != nullptr)
            {
                tPos = target->getComponent<TransformComponent>().getPosition();
            }
        }
        a.setTarget(target);
    }
    if (a.hasTarget())
    {
        sf::Vector2f diff = a.getTarget()->getComponent<TransformComponent>().getPosition() - ePos;
        sf::Vector2f mvt;
        if (thor::length(diff) > e->getComponent<WeaponComponent>().getRange() - 16.f)
        {
            mvt = thor::unitVector<float>(diff) * dt.asSeconds() * m.getSpeed();
            CollisionComponent& c = e->getComponent<CollisionComponent>();
            c.setCenter(ePos + mvt);
            if (collision(c.getCollisionBox(), mvt, e->getId()))
            {
                a.setTarget(nullptr);
            }
            e->getComponent<TransformComponent>().move(mvt);
            c.setCenter(e->getComponent<TransformComponent>().getPosition());
        }

        // For Animation
        if (mvt != sf::Vector2f(0.f,0.f))
        {
            e->getComponent<MovementComponent>().walking(dt);
        }
        else
        {
            e->getComponent<MovementComponent>().stopWalking();
        }
    }
    else
    {
        e->getComponent<MovementComponent>().stopWalking();
        // TODO (#3#): Lambda Movement
    }
}

void AIControllerSystem::handlePacific(es::Entity::Ptr e, sf::Time dt)
{
    AIComponent& a = e->getComponent<AIComponent>();
    MovementComponent& m = e->getComponent<MovementComponent>();
    sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition();

    if (!a.hasTarget() && mManager != nullptr)
    {
        es::EntityManager::EntityArray targetList = mManager->getByFilter(AIComponent::getTargetFilter());
        es::Entity::Ptr target = nullptr;
        sf::Vector2f tPos;
        for (unsigned int i = 0; i < targetList.size(); i++)
        {
            if (targetList[i] != nullptr)
            {
                sf::Vector2f tePos = targetList[i]->getComponent<TransformComponent>().getPosition();
                if (targetList[i]->getId() != e->getId()
                && targetList[i]->getComponent<LifeComponent>().isAlive()
                && thor::length(ePos - tePos)
                < a.getViewDistance())
                {
                    if (targetList[i]->hasComponent<AIComponent>())
                    {
                        if (targetList[i]->getComponent<AIComponent>().isMonster())
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
            }
            if (target != nullptr)
            {
                tPos = target->getComponent<TransformComponent>().getPosition();
            }
        }
        a.setTarget(target);
    }
    if (a.hasTarget())
    {
        sf::Vector2f diff = a.getTarget()->getComponent<TransformComponent>().getPosition() - ePos;
        sf::Vector2f mvt;
        if (thor::length(diff) > 0.f)
        {
            mvt = thor::unitVector<float>(-diff) * dt.asSeconds() * m.getSpeed();
            CollisionComponent& c = e->getComponent<CollisionComponent>();
            c.setCenter(ePos + mvt);
            if (collision(c.getCollisionBox(), mvt, e->getId()))
            {
                a.setTarget(nullptr);
            }
            e->getComponent<TransformComponent>().move(mvt);
            c.setCenter(e->getComponent<TransformComponent>().getPosition());
        }

        // For Animation
        if (mvt != sf::Vector2f(0.f,0.f))
        {
            e->getComponent<MovementComponent>().walking(dt);
        }
        else
        {
            e->getComponent<MovementComponent>().stopWalking();
        }
    }
    else
    {
        e->getComponent<MovementComponent>().stopWalking();
        // TODO (#3#): Lambda Movement
    }
}

void AIControllerSystem::handleAttack(es::Entity::Ptr e)
{
    if (e->getComponent<AIComponent>().hasTarget() && e->getComponent<AIComponent>().isFighter() && e->hasComponent<WeaponComponent>())
    {
        WeaponComponent& w = e->getComponent<WeaponComponent>();
        es::Entity::Ptr target = e->getComponent<AIComponent>().getTarget();
        if (thor::length(e->getComponent<TransformComponent>().getPosition() - target->getComponent<TransformComponent>().getPosition()) < w.getRange()
        && w.canAttack())
        {
            target->getComponent<LifeComponent>().inflige(w.getDamage());
            w.attack();
        }
    }
}
