#include "RenderSystem.hpp"

RenderSystem::RenderSystem()
{
    mFilter.push_back(TransformComponent::getId());
    mFilter.push_back(SpriteComponent::getId());

    mRenderDebug = false;
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
        // TODO : Sort
        return a->getComponent<TransformComponent>().getPosition().y < b->getComponent<TransformComponent>().getPosition().y;
    });

    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        sf::RenderStates states;
        states.transform *= mEntities[i]->getComponent<TransformComponent>().getTransform();

        // Weapon
        if (mEntities[i]->hasComponent<WeaponComponent>() && mEntities[i]->hasComponent<MovementComponent>())
        {
            // TODO : Handle Weapon Rendering
            /*MovementComponent::Direction dir = mEntities[i]->getComponent<MovementComponent>().getDirection();
            if (dir == MovementComponent::Direction::W || dir == MovementComponent::Direction::N)
            {
                target.draw(mEntities[i]->getComponent<WeaponComponent>(),states);
            }*/
        }

        // Sprite
        target.draw(mEntities[i]->getComponent<SpriteComponent>(),states);

        // Weapon
        if (mEntities[i]->hasComponent<WeaponComponent>() && mEntities[i]->hasComponent<MovementComponent>())
        {
            // TODO : Handle Weapon Rendering
            /*MovementComponent::Direction dir = mEntities[i]->getComponent<MovementComponent>().getDirection();
            if (dir == MovementComponent::Direction::S || dir == MovementComponent::Direction::E)
            {
                target.draw(mEntities[i]->getComponent<WeaponComponent>(),states);
            }*/
        }

        // Life Bar
        if (mEntities[i]->hasComponent<LifeComponent>())
        {
            target.draw(mEntities[i]->getComponent<LifeComponent>(), states);
        }

        if (mRenderDebug)
        {
            // Collision Box
            if (mEntities[i]->hasComponent<CollisionComponent>())
            {
                target.draw(mEntities[i]->getComponent<CollisionComponent>(), states);
            }

            // Bounding Box
            if (mEntities[i]->hasComponent<TransformComponent>())
            {
                target.draw(mEntities[i]->getComponent<BoxComponent>(), states);
            }
        }
    }
}

void RenderSystem::renderDebug(bool renderDebug)
{
    mRenderDebug = renderDebug;
}


