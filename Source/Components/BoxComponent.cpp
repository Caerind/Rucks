#include "BoxComponent.hpp"
#include "../../Lib/EntitySystem/Entity.hpp"
#include "TransformComponent.hpp"

BoxComponent::BoxComponent()
{
}

std::string BoxComponent::getId()
{
    return "BoxComponent";
}

void BoxComponent::setSize(float sizeX, float sizeY)
{
    mSize.x = sizeX;
    mSize.y = sizeY;
}

void BoxComponent::setSize(sf::Vector2f const& size)
{
    mSize = size;
}

sf::Vector2f BoxComponent::getSize() const
{
    return mSize;
}

sf::FloatRect BoxComponent::getBounds() const
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

bool BoxComponent::intersects(sf::FloatRect const& rect) const
{
    return getBounds().intersects(rect);
}

void BoxComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape shape;
    shape.setSize(getSize());
    shape.setPosition(getPosition()-getOrigin());
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1.2f);
    shape.setOutlineColor(sf::Color::Green);
    target.draw(shape,states);
}
