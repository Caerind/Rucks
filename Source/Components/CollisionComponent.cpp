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

