#include "Weapon.hpp"

Weapon::Weapon()
{
    mType = Type::None;
}

void Weapon::setType(Type type)
{
    mType = type;
}

Weapon::Type Weapon::getType() const
{
    return mType;
}

bool Weapon::isLongRange() const
{
    return mType == Type::Bow;
}

ProjectileComponent::Type Weapon::getProjectileType() const
{
    switch (mType)
    {
        case Type::Bow: return ProjectileComponent::Type::Arrow; break;
    }
    return ProjectileComponent::Type::None;
}


void Weapon::setRange(float range)
{
    mRange = range;
}

float Weapon::getRange() const
{
    return mRange;
}

void Weapon::setDamage(int damage)
{
    mDamage = damage;
}

int Weapon::getDamage() const
{
    return mDamage;
}

void Weapon::setCooldown(sf::Time cooldown)
{
    mCooldown = cooldown;
}

sf::Time Weapon::getCooldown() const
{
    return mCooldown;
}

bool Weapon::isWeapon() const
{
    return true;
}
