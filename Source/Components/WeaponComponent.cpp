#include "WeaponComponent.hpp"
#include "../World.hpp"
#include "../Prefab.hpp"
#include "../../Aharos/Application/Application.hpp"

WeaponComponent::WeaponComponent()
{
    mWeapon = nullptr;
    rd::Renderer::add(this);
}

WeaponComponent::~WeaponComponent()
{
    rd::Renderer::remove(this);
}

std::string WeaponComponent::getId()
{
    return "WeaponComponent";
}

void WeaponComponent::render(sf::RenderTarget& target)
{
    if (mWeapon != nullptr)
    {
        sf::Vector2f pos = mPosition;
        if (hasParent())
        {
            if (mParent->hasComponent<TransformComponent>())
            {
                pos += mParent->getComponent<TransformComponent>().getPosition();
            }
        }
        rd::Sprite::setPosition(pos);
        rd::Sprite::render(target);
    }
}

void WeaponComponent::setWeapon(Weapon::Ptr weapon)
{
    mWeapon = weapon;
    if (mWeapon != nullptr)
    {
        setTexture(World::instance().getResources().getTexture("weapons"));
        setTextureRect(sf::IntRect(mWeapon->getType() * 32, 0, 32, 64));
        setOrigin(16.f,64.f);
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

void WeaponComponent::setDamage(sf::Vector2i damageRange)
{
    mDamage = damageRange;
}

void WeaponComponent::setDamage(int damageMin, int damageMax)
{
    mDamage.x = damageMin;
    mDamage.y = damageMax;
}

void WeaponComponent::setDamageMin(int damageMin)
{
    mDamage.x = damageMin;
}

void WeaponComponent::setDamageMax(int damageMax)
{
    mDamage.y = damageMax;
}

int WeaponComponent::getDamageMin() const
{
    if (hasWeapon())
    {
        return mWeapon->getDamageMin();
    }
    return mDamage.x;
}

int WeaponComponent::getDamageMax() const
{
    if (hasWeapon())
    {
        return mWeapon->getDamageMax();
    }
    return mDamage.y;
}

sf::Vector2i WeaponComponent::getDamageRange() const
{
    if (hasWeapon())
    {
        return mWeapon->getDamageRange();
    }
    return mDamage;
}

int WeaponComponent::getDamage() const
{
    if (hasWeapon())
    {
        return mWeapon->getDamage();
    }
    return thor::random(mDamage.x,mDamage.y);
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

void WeaponComponent::attack()
{
    mTimeSinceLastAttack.restart();
}

void WeaponComponent::attack(es::Entity::Ptr target)
{
    if (canAttack() && !isLongRange() && hasParent() && target != nullptr)
    {
        if (getRange() >= thor::length(target->getComponent<TransformComponent>().getPosition() - mParent->getComponent<TransformComponent>().getPosition()))
        {
            if (target->hasComponent<StatComponent>() && mParent->hasComponent<StatComponent>())
            {
                StatComponent& sT = target->getComponent<StatComponent>();
                StatComponent& sP = mParent->getComponent<StatComponent>();
                if (sT.isAlive())
                {
                    int damage = getDamage() + sP.getStrength(); // TODO : Better Formumle for Damage
                    if (sT.inflige(damage))
                    {
                        sP.addExperience(10); // TODO : Add Experience
                    }
                }
            }
        }
    }
    mTimeSinceLastAttack.restart();
}

void WeaponComponent::attack(sf::Vector2f const& direction)
{
    if (canAttack() && isLongRange() && hasParent())
    {
        sf::Vector2f pos = rd::Sprite::getPosition();
        World::instance().createProjectile(pos, direction, mParent->getId());
    }
    mTimeSinceLastAttack.restart();
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
    mPosition = sf::Vector2f(x,y);
    rd::Sprite::setRotation(rotation);
}
