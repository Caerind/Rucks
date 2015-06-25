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

        // Weapon
        if (mEntities[i]->hasComponent<WeaponComponent>() && mEntities[i]->hasComponent<MovementComponent>())
        {
            MovementComponent::Direction dir = mEntities[i]->getComponent<MovementComponent>().getDirection();
            if (dir == MovementComponent::Direction::W || dir == MovementComponent::Direction::N)
            {
                target.draw(mEntities[i]->getComponent<WeaponComponent>(),states);
            }
        }

        // Sprite
        target.draw(mEntities[i]->getComponent<SpriteComponent>(),states);

        // Weapon
        if (mEntities[i]->hasComponent<WeaponComponent>() && mEntities[i]->hasComponent<MovementComponent>())
        {
            MovementComponent::Direction dir = mEntities[i]->getComponent<MovementComponent>().getDirection();
            if (dir == MovementComponent::Direction::S || dir == MovementComponent::Direction::E)
            {
                target.draw(mEntities[i]->getComponent<WeaponComponent>(),states);
            }
        }

        // Life
        if (mEntities[i]->hasComponent<LifeComponent>())
        {
            // TODO (#5#): Life Bar Position
            mEntities[i]->getComponent<LifeComponent>().renderLifeBar(target,states);
        }

        // Debug
        if (mEntities[i]->hasComponent<CollisionComponent>())
        {
            mEntities[i]->getComponent<CollisionComponent>().renderCollisionBox(target);
        }
        if (mEntities[i]->hasComponent<TransformComponent>())
        {
            mEntities[i]->getComponent<TransformComponent>().renderBoundingBox(target);
        }
    }
}


