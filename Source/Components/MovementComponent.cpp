#include "MovementComponent.hpp"

MovementComponent::MovementComponent()
{
    mSpeed = 100.f;
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
