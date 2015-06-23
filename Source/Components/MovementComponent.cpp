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

void MovementComponent::setLastMovement(sf::Vector2f movement)
{
    mLastMovement = movement;
}

sf::Vector2f MovementComponent::getLastMovement() const
{
    return mLastMovement;
}

void MovementComponent::setLookAt(sf::Vector2f lookAt)
{
    mLookAt = lookAt;
}

sf::Vector2f MovementComponent::getLookAt() const
{
    return mLookAt;
}

void MovementComponent::resetWalkTime()
{
    mWalkTime = sf::Time::Zero;
}

void MovementComponent::addWalkTime(sf::Time dt)
{
    mWalkTime += dt;
}

sf::Time MovementComponent::getWalkTime() const
{
    return mWalkTime;
}
