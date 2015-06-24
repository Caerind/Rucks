#include "WeaponComponent.hpp"
#include "../World.hpp"

WeaponComponent::WeaponComponent(WeaponComponent::Type type)
{
    setType(type);
}

WeaponComponent::WeaponComponent(float range, unsigned int damage, sf::Time cooldown)
{
    mType = WeaponComponent::None;
    mRange = range;
    mDamage = damage;
    mCooldown = cooldown;
}

std::string WeaponComponent::getId()
{
    return "WeaponComponent";
}

void WeaponComponent::setType(WeaponComponent::Type type)
{
    mType = type;
    mRange = getRange(type);
    mDamage = getDamage(type);
    mCooldown = getCooldown(type);
    //mWeaponSprite.setTexture(World::instance().getResources().getTexture(getTextureId(type)));
    mWeaponSprite.setTextureRect(getTextureRect(type));
}

WeaponComponent::Type WeaponComponent::getType() const
{
    return mType;
}

bool WeaponComponent::isLongRange() const
{
    // TODO (#7#): Long Range Weapons
    return false;
}

void WeaponComponent::setRange(float range)
{
    mRange = range;
}

float WeaponComponent::getRange() const
{
    return mRange;
}

void WeaponComponent::setDamage(unsigned int damage)
{
    mDamage = damage;
}

unsigned int WeaponComponent::getDamage() const
{
    return mDamage;
}

void WeaponComponent::setCooldown(sf::Time cooldown)
{
    mCooldown = cooldown;
}

sf::Time WeaponComponent::getCooldown() const
{
    return mCooldown;
}

void WeaponComponent::attack()
{
    mTimeSinceLastAttack.restart();
}

bool WeaponComponent::canAttack()
{
    return mTimeSinceLastAttack.getElapsedTime() >= mCooldown;
}

void WeaponComponent::setWeaponTransform(sf::Vector2f const& position, float rotation)
{
    setPosition(position);
    setRotation(rotation);
}

void WeaponComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mWeaponSprite,states);
}

float WeaponComponent::getRange(WeaponComponent::Type type)
{
    return 50.f;
}

unsigned int WeaponComponent::getDamage(WeaponComponent::Type type)
{
    switch (type)
    {
        case WeaponComponent::Type::None: return 10;
        case WeaponComponent::Type::Sword: return 20;
    }
    return 10;
}

sf::Time WeaponComponent::getCooldown(WeaponComponent::Type type)
{
    return sf::seconds(0.3f);
}

std::string WeaponComponent::getTextureId(WeaponComponent::Type type)
{
    return "weapons";
}

sf::IntRect WeaponComponent::getTextureRect(WeaponComponent::Type type)
{
    return sf::IntRect(type * 32, 0, 32, 64);
}

void WeaponComponent::loadWeaponTextures()
{
    World::instance().getResources().loadTexture("weapons","Assets/Textures/weapons.png");
    World::instance().getResources().getTexture("weapons").setSmooth(true);
}

void WeaponComponent::releaseWeaponTextures()
{
    World::instance().getResources().releaseTexture("weapons");
}

