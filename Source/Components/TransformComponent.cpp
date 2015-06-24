#include "TransformComponent.hpp"
#include "../World.hpp"

TransformComponent::TransformComponent(float x, float y, float w, float h)
{
    setPosition(x,y);
    mSize.x = w;
    mSize.y = h;
}

TransformComponent::TransformComponent(sf::Vector2f const& pos, sf::Vector2f const& size)
{
    setPosition(pos);
    mSize = size;
}

std::string TransformComponent::getId()
{
    return "TransformComponent";
}

void TransformComponent::setSize(sf::Vector2f const& size)
{
    mSize = size;
}

sf::Vector2f TransformComponent::getSize() const
{
    return mSize;
}

sf::FloatRect TransformComponent::getBoundingBox() const
{
    return sf::FloatRect(getPosition().x - mSize.x/2, getPosition().y - mSize.y/2, mSize.x, mSize.y);
}

void TransformComponent::renderBoundingBox(sf::RenderTarget& target)
{
    sf::RectangleShape r;
    r.setSize(mSize);
    r.setPosition(getPosition().x - mSize.x/2, getPosition().y - mSize.y/2);
    r.setFillColor(sf::Color::Transparent);
    r.setOutlineColor(sf::Color::Green);
    r.setOutlineThickness(1.2f);
    target.draw(r);
}
