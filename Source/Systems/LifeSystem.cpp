#include "LifeSystem.hpp"

LifeSystem::LifeSystem()
{
    mFilter.requires(LifeComponent::getId());
}

std::string LifeSystem::getId()
{
    return "LifeSystem";
}

void LifeSystem::update()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getComponent<LifeComponent>().isDead())
        {
            if (mEntities[i]->hasComponent<PlayerComponent>())
            {
                mEntities[i]->getComponent<LifeComponent>().fullRestore();
                if (mEntities[i]->hasComponent<TransformComponent>())
                {
                    mEntities[i]->getComponent<TransformComponent>().setPosition(0.f,0.f);
                }
            }
            else
            {
                mManager->remove(mEntities[i]);
            }
        }
        else
        {
            if (mRegenerationClock.getElapsedTime() > sf::seconds(1.f))
            {
                if (mEntities[i]->hasComponent<AIComponent>())
                {
                    if (!mEntities[i]->getComponent<AIComponent>().hasTarget())
                    {
                        mEntities[i]->getComponent<LifeComponent>().restore(1);
                    }
                }
                else if (mEntities[i]->hasComponent<PlayerComponent>())
                {
                    mEntities[i]->getComponent<LifeComponent>().restore(1);
                }
            }
        }
    }
    if (mRegenerationClock.getElapsedTime() > sf::seconds(1.f))
    {
        mRegenerationClock.restart();
    }
}
