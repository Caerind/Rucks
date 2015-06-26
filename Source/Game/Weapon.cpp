#include "Weapon.hpp"

Weapon::Weapon()
{
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
