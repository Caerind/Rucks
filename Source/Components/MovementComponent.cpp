#include "MovementComponent.hpp"

MovementComponent::MovementComponent(float speed)
{
    mSpeed = speed;
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
