#include "MovementSystem.hpp"
#include "../World.hpp"

MovementSystem::MovementSystem()
{
    mFilter.requires(TransformComponent::getId());
    mFilter.requires(MovementComponent::getId());
}

std::string MovementSystem::getId()
{
    return "MovementSystem";
}

void MovementSystem::update(sf::Time dt)
{
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        sf::Vector2f mvt;
        sf::Vector2f direction = mEntities[i]->getComponent<MovementComponent>().getDirection();
        float speed = mEntities[i]->getComponent<MovementComponent>().getSpeed();

        if (mEntities[i]->hasComponent<HumanComponent>())
        {
            HumanComponent::Direction dirEnt = mEntities[i]->getComponent<HumanComponent>().getDirection();
            HumanComponent::Direction dirMvt = HumanComponent::getDirection(direction);
            if (dirEnt == dirMvt + 2 || dirEnt + 2 == dirMvt)
            {
                speed *= 0.8f; // Reduce the movement if we go backward
            }
        }

        mvt = speed * direction * dt.asSeconds();

        if (mEntities[i]->hasComponent<CollisionComponent>())
        {
            if (World::instance().getEntities().getSystem<CollisionSystem>().handle(mEntities[i],mvt))
            {
                if (mEntities[i]->hasComponent<AIComponent>())
                {
                    mEntities[i]->getComponent<AIComponent>().setTargetId(0);
                    // TODO : A*
                }
            }
        }

        // Finally move it
        mEntities[i]->getComponent<TransformComponent>().move(mvt);

        // Human walking
        if (mEntities[i]->hasComponent<HumanComponent>())
        {
            if (mvt != sf::Vector2f())
            {
                mEntities[i]->getComponent<HumanComponent>().addWalkTime(dt);
            }
            else
            {
                mEntities[i]->getComponent<HumanComponent>().resetWalkTime();
            }
        }

        // Projectile distance
        if (mEntities[i]->hasComponent<ProjectileComponent>())
        {
            mEntities[i]->getComponent<ProjectileComponent>().addDistanceTraveled(mvt);
        }
    }
}
