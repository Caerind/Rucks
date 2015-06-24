#include "WeaponComponent.hpp"

WeaponComponent::WeaponComponent(float range, unsigned int damage, sf::Time cooldown)
{
    mRange = range;
    mDamage = damage;
    mCooldown = cooldown;
}

std::string WeaponComponent::getId()
{
    return "WeaponComponent";
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

void WeaponComponent::renderWeapon(sf::RenderTarget& target, sf::RenderStates states)
{

}
