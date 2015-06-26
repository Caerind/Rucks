#include "LifeSystem.hpp"

LifeSystem::LifeSystem()
{
    mFilter.push_back(LifeComponent::getId());
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
    }
}
