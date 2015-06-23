#include "AIControllerSystem.hpp"

AIControllerSystem::AIControllerSystem()
{
    mFilter.push_back(TransformComponent::getId());
    mFilter.push_back(SpriteComponent::getId());
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
            // TODO : AI not Monster
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
        sf::Vector2f diff = m.getLookAt() - e->getComponent<SpriteComponent>().getOrigin() - e->getComponent<TransformComponent>().getPosition();
        sf::Vector2f mvt;
        if (diff.x != 0.f && diff.y != 0.f)
        {
            mvt = thor::unitVector<float>(diff);
        }
        mvt *= dt.asSeconds() * m.getSpeed();
        // TODO : Check Collisions
        e->getComponent<TransformComponent>().move(mvt);
        m.setLastMovement(mvt);
        m.setLookAt(a.getTarget()->getComponent<TransformComponent>().getPosition() + a.getTarget()->getComponent<SpriteComponent>().getOrigin());
    }
    else
    {
        m.setLastMovement(sf::Vector2f(0.f,0.f));
    }
}
