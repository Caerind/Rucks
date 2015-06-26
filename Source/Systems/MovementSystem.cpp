#include "MovementSystem.hpp"
#include "../World.hpp"

MovementSystem::MovementSystem()
{
    mFilter.push_back(TransformComponent::getId());
    mFilter.push_back(MovementComponent::getId());
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
        mvt = mEntities[i]->getComponent<MovementComponent>().getSpeed() * mEntities[i]->getComponent<MovementComponent>().getDirection() * dt.asSeconds();

        if (mEntities[i]->hasComponent<CollisionComponent>())
        {
            World::instance().getEntities().getSystem<CollisionSystem>().handle(mEntities[i],mvt);
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
    }
}
