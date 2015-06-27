#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem()
{
    mFilter.push_back(CollisionComponent::getId());
    mChunks = nullptr;
}

std::string CollisionSystem::getId()
{
    return "CollisionSystem";
}

void CollisionSystem::setChunks(ChunkManager& chunks)
{
    mChunks = &chunks;
}

bool CollisionSystem::handle(es::Entity::Ptr e, sf::Vector2f& movement)
{
    sf::Vector2f defaultMovement = movement;

    // Move the Collision Box
    sf::FloatRect rect = e->getComponent<CollisionComponent>().getBounds();
    rect.left += movement.x;
    rect.top += movement.y;

    std::vector<sf::FloatRect> rects;

    // Intersecting tiles
    if (mChunks != nullptr)
    {
        mChunks->collision(rect,rects);
    }

    // Intersecting entities
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getId() != e->getId() && mEntities[i]->getComponent<CollisionComponent>().getBounds().intersects(rect))
        {
            rects.push_back(mEntities[i]->getComponent<CollisionComponent>().getBounds());
        }
    }

    if (rects.size() > 0)
    {
        movement = sf::Vector2f();
    }

    return movement != defaultMovement;
}

bool CollisionSystem::projectileCollision(sf::FloatRect const& rect, es::Entity::Ptr& e)
{
    std::vector<sf::FloatRect> rects;
    if (mChunks != nullptr)
    {
        if (mChunks->collision(rect,rects))
        {
            e = nullptr;
            return true;
        }
    }
    std::vector<es::Entity::Ptr> es;
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getComponent<CollisionComponent>().intersects(rect))
        {
            es.push_back(mEntities[i]);
        }
    }
    if (es.size() > 0)
    {
        for (unsigned int i = 0; i < es.size(); i++)
        {
            if (es[i]->hasComponent<LifeComponent>())
            {
                e = es[i];
                return true;
            }
        }
    }
    e = nullptr;
    return false;
}
