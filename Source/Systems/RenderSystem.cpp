#include "RenderSystem.hpp"

RenderSystem::RenderSystem()
{
    mFilter.push_back(TransformComponent::getId());
    mFilter.push_back(SpriteComponent::getId());
}

std::string RenderSystem::getId()
{
    return "RenderSystem";
}

void RenderSystem::render(sf::RenderTarget& target)
{
    // TODO : Sort

    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        sf::RenderStates states;
        states.transform *= mEntities[i]->getComponent<TransformComponent>().getTransform();
        target.draw(mEntities[i]->getComponent<SpriteComponent>(),states);

        /*
        if (mEntities[i]->hasComponent<LifeComponent>())
        {
            ...
        }
        */
        /*
        if (mEntities[i]->hasComponent<CollisionComponent>())
        {
            ...
        }
        */
    }
}


