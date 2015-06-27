#include "SpellComponent.hpp"
#include "../../Lib/EntitySystem/Entity.hpp"
#include "../Components.hpp"
#include "../World.hpp"

SpellComponent::SpellComponent()
{
}

std::string SpellComponent::getId()
{
    return "SpellComponent";
}

void SpellComponent::setType(Type type)
{
    mType = type;
}

SpellComponent::Type SpellComponent::getType() const
{
    return mType;
}

void SpellComponent::setRange(float range)
{
    mRange = range;
}

float SpellComponent::getRange() const
{
    return mRange;
}

void SpellComponent::setDamage(int damage)
{
    mDamage = damage;
}

int SpellComponent::getDamage() const
{
    return mDamage;
}

void SpellComponent::setCooldown(sf::Time cooldown)
{
    mCooldown = cooldown;
}

sf::Time SpellComponent::getCooldown() const
{
    return mCooldown;
}

void SpellComponent::spell(sf::Vector2f const& direction)
{
    if (canSpell() && hasParent())
    {
        mTimeSinceLastSpell.restart();
        switch (mType)
        {
            case Type::Fireball:
            {
                if (mParent->hasComponent<TransformComponent>())
                {
                    sf::Vector2f pos = mParent->getComponent<TransformComponent>().getPosition();
                    World::instance().getPrefab().createFireball(pos, std::shared_ptr<es::Entity>(mParent), direction);
                }
            } break;

            case Type::Heal:
            {
                if (mParent->hasComponent<LifeComponent>())
                {
                    mParent->getComponent<LifeComponent>().restore(mDamage);
                }
            } break;
        }
    }
}

bool SpellComponent::canSpell()
{
    return mTimeSinceLastSpell.getElapsedTime() >= mCooldown;
}

sf::Time SpellComponent::getTimeSinceLastSpell() const
{
    return mTimeSinceLastSpell.getElapsedTime();
}
