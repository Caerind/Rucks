#include "Spell.hpp"

////////////////////////////////////////////////////////////
Spell::Spell()
{
    mType = Type::None;
    mName = "";
    mRange = 0.f;
    mDamage = sf::Vector2i();
    mCooldown = sf::Time::Zero;
    mCast = sf::Time::Zero;
    mStricker = nullptr;
    mTarget = nullptr;
    mDirection = sf::Vector2f();
    mPosition = sf::Vector2f();
}

Spell::~Spell()
{
}

void Spell::setStricker(es::Entity::Ptr stricker)
{
    mStricker = stricker;
}

void Spell::setTarget(es::Entity::Ptr target)
{
    mTarget = target;
}

void Spell::setDirection(sf::Vector2f const& direction)
{
    mDirection = direction;
}

void Spell::setPosition(sf::Vector2f const& position)
{
    mPosition = position;
}

Spell::Type Spell::getType() const
{
    return mType;
}

////////////////////////////////////////////////////////////
std::string Spell::getName() const
{
    return mName;
}

////////////////////////////////////////////////////////////
float Spell::getRange() const
{
    return mRange;
}

////////////////////////////////////////////////////////////
int Spell::getDamageMin() const
{
    return mDamage.x;
}

////////////////////////////////////////////////////////////
int Spell::getDamageMax() const
{
    return mDamage.y;
}

////////////////////////////////////////////////////////////
sf::Vector2i Spell::getDamageRange() const
{
    return mDamage;
}

////////////////////////////////////////////////////////////
int Spell::getDamage() const
{
    return thor::random(mDamage.x,mDamage.y);
}

////////////////////////////////////////////////////////////
sf::Time Spell::getCooldown() const
{
    return mCooldown;
}

////////////////////////////////////////////////////////////
sf::Time Spell::getCast() const
{
    return mCast;
}

int Spell::getManaCost() const
{
    return mManaCost;
}

sf::Color Spell::getColor() const
{
    return mColor;
}

sf::Time Spell::getRemainingTime() const
{
    sf::Time dt = mCooldown - mCooldownTimer.getElapsedTime();
    return std::max(dt,sf::Time::Zero);
}

