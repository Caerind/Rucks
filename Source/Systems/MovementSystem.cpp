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
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        sf::Vector2f mvt;
        sf::Vector2f direction = mEntities[i]->getComponent<MovementComponent>().getDirection();
        float speed = mEntities[i]->getComponent<MovementComponent>().getSpeed();
        if (mEntities[i]->hasComponent<PlayerComponent>() && mEntities[i]->hasComponent<AnimationComponent>())
        {
            AnimationComponent::Direction dirEnt = mEntities[i]->getComponent<AnimationComponent>().getDirection();
            AnimationComponent::Direction dirMvt = AnimationComponent::getDirection(direction);
            if (dirEnt == dirMvt + 2 || dirEnt + 2 == dirMvt)
            {
                speed /= 1.20f;
            }
        }
        mvt = speed * direction * dt.asSeconds();

        if (mEntities[i]->hasComponent<CollisionComponent>())
        {
            if (World::instance().getEntities().getSystem<CollisionSystem>().handle(mEntities[i],mvt))
            {
                if (mEntities[i]->hasComponent<AIComponent>())
                {
                    mEntities[i]->getComponent<AIComponent>().setTarget(nullptr);
                }
            }
        }

        mEntities[i]->getComponent<TransformComponent>().move(mvt);

        if (mEntities[i]->hasComponent<AnimationComponent>())
        {
            if (mvt != sf::Vector2f())
            {
                mEntities[i]->getComponent<AnimationComponent>().addWalkTime(dt);
            }
            else
            {
                mEntities[i]->getComponent<AnimationComponent>().resetWalkTime();
            }
        }

        if (mEntities[i]->hasComponent<ProjectileComponent>())
        {
            mEntities[i]->getComponent<ProjectileComponent>().addDistanceTraveled(mvt);
        }
    }
}
