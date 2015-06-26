#include "TransformComponent.hpp"

TransformComponent::TransformComponent(sf::Vector2f const& pos, sf::Vector2f const& origin)
{
    setPosition(pos);
    setOrigin(origin);
}

std::string TransformComponent::getId()
{
    return "TransformComponent";
}
