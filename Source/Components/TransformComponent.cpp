#include "TransformComponent.hpp"

TransformComponent::TransformComponent(float x, float y)
{
    setPosition(x,y);
}

TransformComponent::TransformComponent(sf::Vector2f const& pos)
{
    setPosition(pos);
}

std::string TransformComponent::getId()
{
    return "TransformComponent";
}
