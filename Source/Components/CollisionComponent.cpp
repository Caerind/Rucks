#include "CollisionComponent.hpp"
#include "../../Lib/EntitySystem/Entity.hpp"
#include "TransformComponent.hpp"

CollisionComponent::CollisionComponent()
{
}

std::string CollisionComponent::getId()
{
    return "CollisionComponent";
}

void CollisionComponent::setSize(float sizeX, float sizeY)
{
    mSize.x = sizeX;
    mSize.y = sizeY;
}

void CollisionComponent::setSize(sf::Vector2f const& size)
{
    mSize = size;
}

sf::Vector2f CollisionComponent::getSize() const
{
    return mSize;
}

sf::FloatRect CollisionComponent::getBounds() const
{
    sf::Vector2f position = getPosition()-getOrigin();
    if (hasParent())
    {
        if (mParent->hasComponent<TransformComponent>())
        {
            position += mParent->getComponent<TransformComponent>().getPosition();
        }
    }
    return sf::FloatRect(position,getSize());
}

bool CollisionComponent::intersects(sf::FloatRect const& rect) const
{
    return getBounds().intersects(rect);
}

bool CollisionComponent::contains(sf::Vector2f const& pos) const
{
    return getBounds().contains(pos);
}

void CollisionComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape shape;
    shape.setSize(getSize());
    shape.setPosition(getPosition()-getOrigin());
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1.2f);
    shape.setOutlineColor(sf::Color::Red);
    target.draw(shape,states);
}
