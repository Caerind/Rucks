#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent(sf::Vector2f const& size)
{
    setSize(size);
}

std::string CollisionComponent::getId()
{
    return "CollisionComponent";
}

void CollisionComponent::setSize(sf::Vector2f const& size)
{
    mBounds.width = size.x;
    mBounds.height = size.y;
}

sf::Vector2f CollisionComponent::getSize() const
{
    return sf::Vector2f(mBounds.width, mBounds.height);
}

void CollisionComponent::move(sf::Vector2f const& movement)
{
    mBounds.left += movement.x;
    mBounds.top += movement.y;
}

void CollisionComponent::setCenter(sf::Vector2f const& center)
{
    mBounds.left = center.x - mBounds.width/2;
    mBounds.top = center.y - mBounds.height/2;
}

sf::Vector2f CollisionComponent::getCenter() const
{
    return sf::Vector2f(mBounds.left + mBounds.width/2, mBounds.top + mBounds.height/2);
}

sf::FloatRect CollisionComponent::getBounds() const
{
    return mBounds;
}

void CollisionComponent::render(sf::RenderTarget& target)
{
    sf::RectangleShape r;
    r.setFillColor(sf::Color::Transparent);
    r.setOutlineColor(sf::Color::Red);
    r.setOutlineThickness(1);
    r.setPosition(mBounds.left,mBounds.top);
    r.setSize(getSize());
    target.draw(r);
}

void collision(sf::FloatRect const& rect, sf::Vector2f& movement)
{

}

