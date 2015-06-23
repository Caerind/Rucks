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
    std::sort(mEntities.begin(), mEntities.end(),
    [](es::Entity::Ptr a, es::Entity::Ptr b) -> bool
    {
        return a->getComponent<TransformComponent>().getPosition().y + a->getComponent<SpriteComponent>().getSheetSize().y < b->getComponent<TransformComponent>().getPosition().y + b->getComponent<SpriteComponent>().getSheetSize().y;
    });

    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        sf::RenderStates states;
        states.transform *= mEntities[i]->getComponent<TransformComponent>().getTransform();
        target.draw(mEntities[i]->getComponent<SpriteComponent>(),states);
    }
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->hasComponent<CollisionComponent>())
        {
            mEntities[i]->getComponent<CollisionComponent>().render(target);
        }
    }
}


