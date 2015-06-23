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
        if (mEntities[i]->getComponent<AIComponent>().isMonster())
        {
            handleMonster(mEntities[i],dt);
        }
        else
        {
            if (mEntities[i]->getComponent<AIComponent>().isFighter())
            {
                handleFighter(mEntities[i],dt);
            }
            else
            {
                handlePacific(mEntities[i],dt);
            }
        }
    }
}

void AIControllerSystem::handleMonster(es::Entity::Ptr e, sf::Time dt)
{
    AIComponent& a = e->getComponent<AIComponent>();
    MovementComponent& m = e->getComponent<MovementComponent>();
    sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition() + e->getComponent<SpriteComponent>().getOrigin();

    if (!a.hasTarget() && mManager != nullptr)
    {
        es::EntityManager::EntityArray targetList = mManager->getByFilter(AIComponent::getTargetFilter());
        es::Entity::Ptr target = nullptr;
        sf::Vector2f tPos;
        for (unsigned int i = 0; i < targetList.size(); i++)
        {
            if (targetList[i] != nullptr)
            {
                sf::Vector2f tePos = targetList[i]->getComponent<TransformComponent>().getPosition() + targetList[i]->getComponent<SpriteComponent>().getOrigin();
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
                tPos = target->getComponent<TransformComponent>().getPosition() + target->getComponent<SpriteComponent>().getOrigin();
            }
        }
        a.setTarget(target);
    }
    if (a.hasTarget())
    {
        sf::Vector2f diff = m.getLookAt() - ePos;
        sf::Vector2f mvt;
        if (thor::length(diff) > 32.f)
        {
            mvt = thor::unitVector<float>(diff) * dt.asSeconds() * m.getSpeed();
            CollisionComponent& c = e->getComponent<CollisionComponent>();
            c.setCenter(ePos);
            collision(c.getBounds(), mvt);
            e->getComponent<TransformComponent>().move(mvt);
        }
        m.setLastMovement(mvt);
        m.setLookAt(a.getTarget()->getComponent<TransformComponent>().getPosition() + a.getTarget()->getComponent<SpriteComponent>().getOrigin());
    }
    else
    {
        m.setLastMovement(sf::Vector2f(0.f,0.f));
    }
}

void AIControllerSystem::handleFighter(es::Entity::Ptr e, sf::Time dt)
{
    AIComponent& a = e->getComponent<AIComponent>();
    MovementComponent& m = e->getComponent<MovementComponent>();
    sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition() + e->getComponent<SpriteComponent>().getOrigin();

    if (!a.hasTarget() && mManager != nullptr)
    {
        es::EntityManager::EntityArray targetList = mManager->getByFilter(AIComponent::getTargetFilter());
        es::Entity::Ptr target = nullptr;
        sf::Vector2f tPos;
        for (unsigned int i = 0; i < targetList.size(); i++)
        {
            if (targetList[i] != nullptr)
            {
                sf::Vector2f tePos = targetList[i]->getComponent<TransformComponent>().getPosition() + targetList[i]->getComponent<SpriteComponent>().getOrigin();
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
                tPos = target->getComponent<TransformComponent>().getPosition() + target->getComponent<SpriteComponent>().getOrigin();
            }
        }
        a.setTarget(target);
    }
    if (a.hasTarget())
    {
        sf::Vector2f diff = m.getLookAt() - ePos;
        sf::Vector2f mvt;
        if (thor::length(diff) > 32.f)
        {
            mvt = thor::unitVector<float>(diff) * dt.asSeconds() * m.getSpeed();
            CollisionComponent& c = e->getComponent<CollisionComponent>();
            c.setCenter(ePos);
            collision(c.getBounds(), mvt);
            e->getComponent<TransformComponent>().move(mvt);
        }
        m.setLastMovement(mvt);
        m.setLookAt(a.getTarget()->getComponent<TransformComponent>().getPosition() + a.getTarget()->getComponent<SpriteComponent>().getOrigin());
    }
    else
    {
        m.setLastMovement(sf::Vector2f(0.f,0.f));
    }
}

void AIControllerSystem::handlePacific(es::Entity::Ptr e, sf::Time dt)
{
    AIComponent& a = e->getComponent<AIComponent>();
    MovementComponent& m = e->getComponent<MovementComponent>();
    sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition() + e->getComponent<SpriteComponent>().getOrigin();

    if (!a.hasTarget() && mManager != nullptr)
    {
        es::EntityManager::EntityArray targetList = mManager->getByFilter(AIComponent::getTargetFilter());
        es::Entity::Ptr target = nullptr;
        sf::Vector2f tPos;
        for (unsigned int i = 0; i < targetList.size(); i++)
        {
            if (targetList[i] != nullptr)
            {
                sf::Vector2f tePos = targetList[i]->getComponent<TransformComponent>().getPosition() + targetList[i]->getComponent<SpriteComponent>().getOrigin();
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
                tPos = target->getComponent<TransformComponent>().getPosition() + target->getComponent<SpriteComponent>().getOrigin();
            }
        }
        a.setTarget(target);
    }
    if (a.hasTarget())
    {
        sf::Vector2f diff = a.getTarget()->getComponent<TransformComponent>().getPosition() + a.getTarget()->getComponent<SpriteComponent>().getOrigin() - ePos;
        sf::Vector2f mvt;
        if (thor::length(diff) > 32.f)
        {
            mvt = thor::unitVector<float>(-diff) * dt.asSeconds() * m.getSpeed();
            CollisionComponent& c = e->getComponent<CollisionComponent>();
            c.setCenter(ePos);
            collision(c.getBounds(), mvt);
            e->getComponent<TransformComponent>().move(mvt);
        }
        m.setLastMovement(mvt);
        m.setLookAt(a.getTarget()->getComponent<TransformComponent>().getPosition() + a.getTarget()->getComponent<SpriteComponent>().getOrigin() - diff - diff);
    }
    else
    {
        m.setLastMovement(sf::Vector2f(0.f,0.f));
    }
}
