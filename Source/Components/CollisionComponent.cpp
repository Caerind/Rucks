#include "CollisionComponent.hpp"
#include "../../Aharos/EntitySystem/Entity.hpp"
#include "TransformComponent.hpp"

CollisionComponent::CollisionComponent()
{
    rd::Renderer::add(this);
    mZ = 2100.f;
}

CollisionComponent::~CollisionComponent()
{
    rd::Renderer::remove(this);
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

sf::FloatRect CollisionComponent::getBounds()
{
    return sf::FloatRect(getPosition(),getSize());
}

bool CollisionComponent::intersects(sf::FloatRect const& rect)
{
    return getBounds().intersects(rect);
}

bool CollisionComponent::contains(sf::Vector2f const& pos)
{
    return getBounds().contains(pos);
}

void CollisionComponent::render(sf::RenderTarget& target)
{
    sf::RectangleShape shape;
    shape.setSize(getSize());
    shape.setPosition(getPosition());
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1.2f);
    shape.setOutlineColor(sf::Color::Red);
    target.draw(shape);
}

void CollisionComponent::setPosition(sf::Vector2f const& position)
{
    sf::Transformable::setPosition(position);
}

sf::Vector2f CollisionComponent::getPosition() const
{
    sf::Vector2f position = sf::Transformable::getPosition()-getOrigin();
    if (hasParent())
    {
        if (mParent->hasComponent<TransformComponent>())
        {
            position += mParent->getComponent<TransformComponent>().getPosition();
        }
    }
    return position;
}
