#include "WeaponComponent.hpp"
#include "../World.hpp"

WeaponComponent::WeaponComponent()
{
    mWeapon = nullptr;
}

std::string WeaponComponent::getId()
{
    return "WeaponComponent";
}

void WeaponComponent::setWeapon(Weapon::Ptr weapon)
{
    mWeapon = weapon;
    if (weapon != nullptr)
    {
        mWeaponSprite.setTexture(World::instance().getResources().getTexture("weapons"));
        mWeaponSprite.setTextureRect(sf::IntRect(mWeapon->getType() * 32, 0, 32, 64));
    }
}

Weapon::Ptr WeaponComponent::getWeapon() const
{
    return mWeapon;
}

bool WeaponComponent::hasWeapon() const
{
    return mWeapon != nullptr;
}

void WeaponComponent::removeWeapon()
{
    mWeapon = nullptr;
}

Weapon::Ptr WeaponComponent::moveWeapon()
{
    Weapon::Ptr w = nullptr;
    if (hasWeapon())
    {
        w = std::make_shared<Weapon>(*getWeapon());
    }
    removeWeapon();
    return w;
}

bool WeaponComponent::isLongRange() const
{
    if (hasWeapon())
    {
        return mWeapon->isLongRange();
    }
    return false;
}

void WeaponComponent::setRange(float range)
{
    mRange = range;
}

float WeaponComponent::getRange() const
{
    if (hasWeapon())
    {
        return mWeapon->getRange();
    }
    return mRange;
}

void WeaponComponent::setDamage(unsigned int damage)
{
    mDamage = damage;
}

unsigned int WeaponComponent::getDamage() const
{
    if (hasWeapon())
    {
        return mWeapon->getDamage();
    }
    return mDamage;
}

void WeaponComponent::setCooldown(sf::Time cooldown)
{
    mCooldown = cooldown;
}

sf::Time WeaponComponent::getCooldown() const
{
    if (hasWeapon())
    {
        return mWeapon->getCooldown();
    }
    return mCooldown;
}

void WeaponComponent::attack(sf::Vector2f const& direction)
{
    mTimeSinceLastAttack.restart();
    if (isLongRange())
    {
        sf::Vector2f pos = mWeaponSprite.getPosition();
        if (hasParent())
        {
            pos += mParent->getComponent<TransformComponent>().getPosition();
            World::instance().getPrefab().createProjectile(pos, std::shared_ptr<es::Entity>(mParent), direction);
        }
    }
}

bool WeaponComponent::canAttack()
{
    if (hasWeapon())
    {
        return mTimeSinceLastAttack.getElapsedTime() >= mWeapon->getCooldown();
    }
    return mTimeSinceLastAttack.getElapsedTime() >= mCooldown;
}

sf::Time WeaponComponent::getTimeSinceLastAttack() const
{
    return mTimeSinceLastAttack.getElapsedTime();
}

void WeaponComponent::setWeaponTransform(float x, float y, float rotation)
{
    setPosition(x,y);
    setRotation(rotation);
}

void WeaponComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mWeaponSprite,states);
}

/*
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
    return sf::seconds(0.2f);
}

std::string WeaponComponent::getTextureId(WeaponComponent::Type type)
{
    return "weapons";
}

sf::IntRect WeaponComponent::getTextureRect(WeaponComponent::Type type)
{
    return sf::IntRect(type * 32, 0, 32, 64);
}*/

void WeaponComponent::loadWeaponTextures()
{
    World::instance().getResources().loadTexture("weapons","Assets/Textures/weapons.png");
    World::instance().getResources().getTexture("weapons").setSmooth(true);
}

void WeaponComponent::releaseWeaponTextures()
{
    World::instance().getResources().releaseTexture("weapons");
}

