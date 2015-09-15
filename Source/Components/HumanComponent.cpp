#include "HumanComponent.hpp"
#include "../World.hpp"

HumanComponent::HumanComponent()
{
    mZ = 16.f;

    mBody.setTexture(World::instance().getResources().getTexture("male_walkcycle_body"));
    mLegs.setTexture(World::instance().getResources().getTexture("male_walkcycle_legs"));
    mRightArm.setTexture(World::instance().getResources().getTexture("male_walkcycle_rarm"));
    mLeftArm.setTexture(World::instance().getResources().getTexture("male_walkcycle_larm"));

    setTextureRect(sf::IntRect(0,128,64,64));

    mBody.setOrigin(32.f,32.f);
    mLegs.setOrigin(32.f,32.f);
    mRightArm.setOrigin(32.f,32.f);
    mLeftArm.setOrigin(32.f,32.f);

    rd::Renderer::add(this);
}

HumanComponent::~HumanComponent()
{
    rd::Renderer::remove(this);
}

std::string HumanComponent::getId()
{
    return "HumanComponent";
}

void HumanComponent::setTextureRect(sf::IntRect const& tRect)
{
    mBody.setTextureRect(tRect);
    mLegs.setTextureRect(tRect);
    mLeftArm.setTextureRect(tRect);
    mRightArm.setTextureRect(tRect);
}

void HumanComponent::setBodyTextureRect(sf::IntRect const& tRect)
{
    mBody.setTextureRect(tRect);
}

void HumanComponent::setLeftArmTextureRect(sf::IntRect const& tRect)
{
    mLeftArm.setTextureRect(tRect);
}

void HumanComponent::setRightArmTextureRect(sf::IntRect const& tRect)
{
    mRightArm.setTextureRect(tRect);
}

void HumanComponent::setLeftArmTexture(std::string const& id)
{
    mLeftArm.setTexture(World::instance().getResources().getTexture(id));
}

sf::FloatRect HumanComponent::getBounds()
{
    if (hasParent())
    {
        if (mParent->hasComponent<BoxComponent>())
        {
            return mParent->getComponent<BoxComponent>().getBounds();
        }
    }
    return sf::FloatRect();
}

void HumanComponent::render(sf::RenderTarget& target)
{
    setPosition(sf::Vector2f());
    target.draw(mLegs);
    target.draw(mBody);
    target.draw(mLeftArm);
    target.draw(mRightArm);
}

void HumanComponent::setPosition(sf::Vector2f const& position)
{
    sf::Vector2f p = getPosition();
    mLegs.setPosition(p);
    mBody.setPosition(p);
    mLeftArm.setPosition(p);
    mRightArm.setPosition(p);
}

sf::Vector2f HumanComponent::getPosition() const
{
    if (hasParent())
    {
        if (mParent->hasComponent<TransformComponent>())
        {
            return mParent->getComponent<TransformComponent>().getPosition();
        }
    }
    return sf::Vector2f();
}

void HumanComponent::setDirection(sf::Vector2f const& lookAt)
{
    sf::Vector2f diff = lookAt;
    if (hasParent())
    {
        if (mParent->hasComponent<TransformComponent>())
        {
            diff -= mParent->getComponent<TransformComponent>().getPosition();
        }
    }
    mDirection = getDirection(diff);
}

void HumanComponent::setDirection(Direction direction)
{
    mDirection = direction;
}

HumanComponent::Direction HumanComponent::getDirection() const
{
    return mDirection;
}

sf::Vector2f HumanComponent::getMovement() const
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

HumanComponent::Direction HumanComponent::getDirection(sf::Vector2f const& direction)
{
    if (std::abs(direction.x) > std::abs(direction.y)) // W || E
    {
        if (direction.x >= 0)
        {
            return Direction::E;
        }
        else
        {
            return Direction::W;
        }
    }
    else // N || S
    {
        if (direction.y >= 0)
        {
            return Direction::S;
        }
        else
        {
            return Direction::N;
        }
    }
    return Direction::S;
}

void HumanComponent::addWalkTime(sf::Time dt)
{
    mWalkTime += dt;
}

void HumanComponent::resetWalkTime()
{
    mWalkTime = sf::Time::Zero;
}

sf::Time HumanComponent::getWalkTime() const
{
    return mWalkTime;
}

sf::Time HumanComponent::getWalkDuration() const
{
    return sf::seconds(0.8);
}

sf::Time HumanComponent::getCastDuration() const
{
    return sf::seconds(0.8);
}

sf::Vector2i HumanComponent::getSheetSize() const
{
    return sf::Vector2i(64,64);
}

sf::Vector2u HumanComponent::getTextureSize() const
{
    if (mBody.getTexture() != nullptr)
    {
        return mBody.getTexture()->getSize();
    }
    return sf::Vector2u(1,1);
}
