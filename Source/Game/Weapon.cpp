#include "Weapon.hpp"

Weapon::Weapon()
{
    setType(Type::Sword);
}

void Weapon::setType(Type type)
{
    mType = type;
    switch (mType)
    {
        case Type::Sword:
        {
            mName = "Sword";
            mPrice = 10;
            mRange = 50.f;
            mDamage = sf::Vector2i(10,15);
            mCooldown = sf::seconds(0.3f);
        } break;

        case Type::Bow:
        {
            mName = "Bow";
            mPrice = 10;
            mRange = 500.f;
            mDamage = sf::Vector2i(10,15);
            mCooldown = sf::seconds(1.f);
        } break;
    }
}

Weapon::Type Weapon::getType() const
{
    return mType;
}

bool Weapon::isLongRange() const
{
    return mType == Type::Bow;
}

void Weapon::setRange(float range)
{
    mRange = range;
}

float Weapon::getRange() const
{
    return mRange;
}

void Weapon::setDamage(sf::Vector2i damageRange)
{
    mDamage = damageRange;
}

void Weapon::setDamage(int damageMin, int damageMax)
{
    mDamage.x = damageMin;
    mDamage.y = damageMax;
}

void Weapon::setDamageMin(int damageMin)
{
    mDamage.x = damageMin;
}

void Weapon::setDamageMax(int damageMax)
{
    mDamage.y = damageMax;
}

int Weapon::getDamageMin() const
{
    return mDamage.x;
}

int Weapon::getDamageMax() const
{
    return mDamage.y;
}

sf::Vector2i Weapon::getDamageRange() const
{
    return mDamage;
}

int Weapon::getDamage() const
{
    return thor::random(mDamage.x,mDamage.y);
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
