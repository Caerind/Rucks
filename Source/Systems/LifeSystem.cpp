#include "LifeSystem.hpp"

LifeSystem::LifeSystem()
{
    mFilter.requires(StatComponent::getId());
}

std::string LifeSystem::getId()
{
    return "LifeSystem";
}

void LifeSystem::update()
{
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getComponent<StatComponent>().isDead())
        {
            if (mEntities[i]->hasComponent<PlayerComponent>())
            {
                mEntities[i]->getComponent<StatComponent>().fullRestoreLife();
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
            // TODO : Improve Regen System
            if (mRegenerationClock.getElapsedTime() > sf::seconds(1.f))
            {
                mEntities[i]->getComponent<StatComponent>().restoreLife(1);
                mEntities[i]->getComponent<StatComponent>().restoreMana(1);
            }
        }
    }
    if (mRegenerationClock.getElapsedTime() > sf::seconds(1.f))
    {
        mRegenerationClock.restart();
    }
}
