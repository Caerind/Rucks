#include "TransformComponent.hpp"

TransformComponent::TransformComponent(float x, float y)
{
    setPosition(x,y);
}

TransformComponent::TransformComponent(sf::Vector2f pos)
{
    mPosition = pos;
}

std::string TransformComponent::getId()
{
    return "TransformComponent";
}

void TransformComponent::setPosition(float x, float y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void TransformComponent::move(float x, float y)
{
    mPosition.x += x;
    mPosition.y += y;
}

void TransformComponent::setPosition(sf::Vector2f pos)
{
    mPosition = pos;
}

void TransformComponent::move(sf::Vector2f movement)
{
    mPosition += movement;
}

sf::Vector2f TransformComponent::getPosition() const
{
    return mPosition;
}
