#include "CollisionComponent.hpp"
#include "../World.hpp"

CollisionComponent::CollisionComponent(sf::FloatRect const& rect)
{
    mBounds = rect;
}

std::string CollisionComponent::getId()
{
    return "CollisionComponent";
}

void CollisionComponent::move(sf::Vector2f const& movement)
{
    mPosition += movement;
}

void CollisionComponent::setCenter(sf::Vector2f const& center)
{
    mPosition = center;
}

sf::Vector2f CollisionComponent::getCenter() const
{
    return mPosition;
}

sf::FloatRect CollisionComponent::getCollisionBox() const
{
    return sf::FloatRect(mPosition.x-mBounds.width/2+mBounds.left,mPosition.y-mBounds.height/2+mBounds.top,mBounds.width,mBounds.height);
}

void CollisionComponent::renderCollisionBox(sf::RenderTarget& target)
{
    sf::RectangleShape r;
    r.setFillColor(sf::Color::Transparent);
    r.setOutlineColor(sf::Color::Red);
    r.setOutlineThickness(1);
    r.setPosition(mPosition.x-mBounds.width/2+mBounds.left,mPosition.y-mBounds.height/2+mBounds.top);
    r.setSize(sf::Vector2f(mBounds.width,mBounds.height));
    target.draw(r);
}

bool collision(sf::FloatRect const& rect, sf::Vector2f& movement, std::size_t id)
{
    std::vector<sf::FloatRect> rects;

    World::instance().getChunks().collision(rect,rects);

    es::ComponentFilter filter;
    filter.push_back(CollisionComponent::getId());
    es::EntityManager::EntityArray entities = World::instance().getEntities().getByFilter(filter);
    for (unsigned int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->getId() != id && entities[i]->getComponent<CollisionComponent>().getCollisionBox().intersects(rect))
        {
            rects.push_back(entities[i]->getComponent<CollisionComponent>().getCollisionBox());
        }
    }

    if (rects.size() > 0)
    {
        // TODO (#7#): Better Collision Handling
        movement = sf::Vector2f(0,0);
        return true;
    }
    return false;
}

