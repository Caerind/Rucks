#include "MovementComponent.hpp"
#include <Thor/Math/Random.hpp>

MovementComponent::MovementComponent()
{
}

std::string MovementComponent::getId()
{
    return "MovementComponent";
}

void MovementComponent::setSpeed(float speed)
{
    mSpeed = speed;
}

float MovementComponent::getSpeed() const
{
    return mSpeed;
}

void MovementComponent::setDirection(sf::Vector2f const& direction)
{
    if (direction != sf::Vector2f())
    {
        mDirection = thor::unitVector<float>(direction);
    }
    else
    {
        mDirection = direction;
    }
}

sf::Vector2f MovementComponent::getDirection() const
{
    return mDirection;
}
