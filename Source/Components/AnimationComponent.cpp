#include "AnimationComponent.hpp"
#include "../../Lib/EntitySystem/Entity.hpp"
#include "TransformComponent.hpp"

AnimationComponent::AnimationComponent()
{
}

std::string AnimationComponent::getId()
{
    return "AnimationComponent";
}

void AnimationComponent::setSheetSize(sf::Vector2i const& sheetSize)
{
    mSheetSize = sheetSize;
}

sf::Vector2i AnimationComponent::getSheetSize() const
{
    return mSheetSize;
}

void AnimationComponent::setDirection(sf::Vector2f const& lookAt)
{
    sf::Vector2f diff = lookAt;
    if (hasParent())
    {
        if (mParent->hasComponent<TransformComponent>())
        {
            diff -= mParent->getComponent<TransformComponent>().getPosition();
        }
    }
    if (std::abs(diff.x) > std::abs(diff.y)) // W || E
    {
        if (diff.x >= 0)
        {
            mDirection = Direction::E;
        }
        else
        {
            mDirection = Direction::W;
        }
    }
    else // N || S
    {
        if (diff.y >= 0)
        {
            mDirection = Direction::S;
        }
        else
        {
            mDirection = Direction::N;
        }
    }
}

void AnimationComponent::setDirection(Direction direction)
{
    mDirection = direction;
}

AnimationComponent::Direction AnimationComponent::getDirection() const
{
    return mDirection;
}

sf::Vector2f AnimationComponent::getMovement() const
{
    switch (mDirection)
    {
        case Direction::N: return sf::Vector2f(0.f,-1.f); break;
        case Direction::W: return sf::Vector2f(-1.f,0.f); break;
        case Direction::S: return sf::Vector2f(0.f,1.f); break;
        case Direction::E: return sf::Vector2f(1.f,0.f); break;
    }
    return sf::Vector2f();
}

void AnimationComponent::addWalkTime(sf::Time dt)
{
    mWalkTime += dt;
}

void AnimationComponent::resetWalkTime()
{
    mWalkTime = sf::Time::Zero;
}

sf::Time AnimationComponent::getWalkTime() const
{
    return mWalkTime;
}

void AnimationComponent::setWalkDuration(sf::Time duration)
{
    mWalkDuration = duration;
}

sf::Time AnimationComponent::getWalkDuration() const
{
    return mWalkDuration;
}
