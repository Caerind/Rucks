#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem(ChunkManager& chunks) : es::System(), mChunks(chunks)
{
    mFilter.push_back(CollisionComponent::getId());
}

std::string CollisionSystem::getId()
{
    return "CollisionSystem";
}

bool CollisionSystem::handle(es::Entity::Ptr e, sf::Vector2f& movement)
{
    sf::Vector2f defaultMovement = movement;

    // Move the Collision Box
    e->getComponent<CollisionComponent>().setCenter(e->getComponent<TransformComponent>().getPosition() + movement);
    sf::FloatRect rect = e->getComponent<CollisionComponent>().getCollisionBox();

    std::vector<sf::FloatRect> rects;

    // Intersecting tiles
    mChunks.collision(rect,rects);

    // Intersecting entities
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getId() != e->getId() && mEntities[i]->getComponent<CollisionComponent>().getCollisionBox().intersects(rect))
        {
            rects.push_back(mEntities[i]->getComponent<CollisionComponent>().getCollisionBox());
        }
    }

    if (rects.size() > 0)
    {
        movement = sf::Vector2f(0.f,0.f);
    }
    else
    {
        // TODO (#7#): Better Collision Handling
        // TODO (#3#): Intersect with a Projectile
    }

    e->getComponent<TransformComponent>().move(movement);
    e->getComponent<CollisionComponent>().setCenter(e->getComponent<TransformComponent>().getPosition());

    return movement != defaultMovement;
}
