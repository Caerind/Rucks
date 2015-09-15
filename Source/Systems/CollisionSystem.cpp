#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem(WorldMap& map)
: mMap(map)
{
    mFilter.requires(CollisionComponent::getId());
}

std::string CollisionSystem::getId()
{
    return "CollisionSystem";
}

bool CollisionSystem::handle(es::Entity::Ptr e, sf::Vector2f& movement)
{
    sf::Vector2f defaultMovement = movement;
    lp::CollisionShape box;
    sf::FloatRect rect;
    if (e != nullptr)
    {
        if (e->hasComponent<CollisionComponent>())
        {
            rect = e->getComponent<CollisionComponent>().getBounds();
            rect.left += movement.x;
            rect.top += movement.y;
            box = lp::CollisionShape(rect);
        }
    }

    // Collisions with entities
    std::vector<lp::CollisionShape> collisions;
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        sf::FloatRect r = mEntities[i]->getComponent<CollisionComponent>().getBounds();
        if (e->getId() != mEntities[i]->getId() && r.intersects(rect))
        {
            collisions.push_back(lp::CollisionShape(r));
        }
    }

    // Collisions with tiles
    std::array<sf::Vector2f,4> points = lp::getPoint<float>(rect);
    std::array<sf::Vector2i,4> coords;
    for (std::size_t j = 0; j < points.size(); j++)
    {
        coords[j] = map::Orthogonal::worldToGlobalCoords(points[j]);
    }
    sf::Vector2i pos;
    for (pos.x = coords[0].x; pos.x <= coords[2].x; ++pos.x)
    {
        for (pos.y = coords[0].y; pos.y <= coords[2].y; ++pos.y)
        {
            for (int k = 0; k < 3; k++)
            {
                if (mMap.isCollide(pos,k))
                {
                    lp::CollisionShape b(mMap.getShape(pos,k));
                    if (box.intersects(b))
                    {
                        collisions.push_back(b);
                    }
                }
            }
        }
    }

    if (collisions.size() > 0)
    {
        movement = sf::Vector2f();
    }

    return movement != defaultMovement;
}

bool CollisionSystem::projectileCollision(sf::FloatRect const& rect, es::Entity::Ptr& e)
{
    e = nullptr;

    lp::CollisionShape box(rect);

    // Collisions with entities
    es::ComponentFilter filter;
    filter.requires(BoxComponent::getId());
    es::EntityArray es = World::instance().getEntities().getByFilter(filter);
    for (std::size_t i = 0; i < es.size(); i++)
    {
        if (es[i]->getComponent<BoxComponent>().intersects(rect) && es[i]->getComponent<BoxComponent>().getBounds() != rect && !es[i]->hasComponent<ItemComponent>())
        {
            if (es[i]->hasComponent<StatComponent>())
            {
                e = es[i];
            }
            return true;
        }
    }

    // Collisions with tiles
    std::array<sf::Vector2f,4> points = lp::getPoint<float>(rect);
    std::array<sf::Vector2i,4> coords;
    for (std::size_t j = 0; j < points.size(); j++)
    {
        coords[j] = map::Orthogonal::worldToGlobalCoords(points[j]);
    }
    sf::Vector2i pos;
    for (pos.x = coords[0].x; pos.x <= coords[2].x; ++pos.x)
    {
        for (pos.y = coords[0].y; pos.y <= coords[2].y; ++pos.y)
        {
            for (int k = 1; k < 3; k++) // We doesnt care of layer 0 (ground)
            {
                if (mMap.isCollide(pos,k))
                {
                    lp::CollisionShape b(mMap.getShape(pos,k));
                    if (box.intersects(b))
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
