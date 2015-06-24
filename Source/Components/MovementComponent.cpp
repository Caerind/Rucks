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

void MovementComponent::setDirection(MovementComponent::Direction direction)
{
    mDirection = direction;
}

void MovementComponent::setDirection(sf::Vector2f const& position, sf::Vector2f const& lookAt)
{
    sf::Vector2f diff = lookAt - position;
    float angle = static_cast<float>(atan2(diff.y,diff.x) * 180 / 3.14159265);
    if((angle > 0 && angle < 45) || (angle >= -45 && angle <= 0))
        mDirection = MovementComponent::Direction::E;
    else if(angle >= 45 && angle < 135)
        mDirection = MovementComponent::Direction::S;
    else if((angle >= 135 && angle <= 180) || (angle >= -180 && angle < -135))
        mDirection = MovementComponent::Direction::W;
    else
        mDirection = MovementComponent::Direction::N;
}

MovementComponent::Direction MovementComponent::getDirection() const
{
    return mDirection;
}

void MovementComponent::lastMovement(sf::Vector2f const& movement, sf::Time dt)
{
    if (movement != sf::Vector2f(0.f,0.f))
    {
        walking(dt);
    }
    else
    {
        stopWalking();
    }
}

void MovementComponent::stopWalking()
{
    mWalkTime = sf::Time::Zero;
}

void MovementComponent::walking(sf::Time dt)
{
    mWalkTime += dt;
    if (mWalkTime >= sf::seconds(0.8f))
    {
        stopWalking();
    }
}

sf::Time MovementComponent::getWalkTime() const
{
    return mWalkTime;
}

void MovementComponent::update(sf::Time dt, sf::Vector2f const& movement, sf::Vector2f const& position, sf::Vector2f const& lookAt)
{
    lastMovement(movement,dt);
    setDirection(position,lookAt);
}
