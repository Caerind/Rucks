#include "SpellComponent.hpp"
#include "../../Lib/EntitySystem/Entity.hpp"
#include "../Components.hpp"
#include "../World.hpp"

SpellComponent::SpellComponent()
{
}

SpellComponent::~SpellComponent()
{
    for (std::size_t i = 0; i < mSpells.size(); i++)
    {
        delete mSpells[i];
        mSpells[i] = nullptr;
    }
    mSpells.clear();
}

std::string SpellComponent::getId()
{
    return "SpellComponent";
}

void SpellComponent::learnSpell(Spell* spell)
{
    mSpells.push_back(spell);
}

std::size_t SpellComponent::getSpellCount() const
{
    return mSpells.size();
}

void SpellComponent::setActiveSpell(std::size_t id)
{
    mActiveSpell = id;
}

std::size_t SpellComponent::getActiveSpellId() const
{
    return mActiveSpell;
}

Spell* SpellComponent::getActiveSpell()
{
    return getSpell(mActiveSpell);
}

Spell* SpellComponent::getSpell(std::size_t id)
{
    if (id >= 0 && id < mSpells.size())
    {
        return mSpells[id];
    }
    return nullptr;
}

/*
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
                if (mParent->hasComponent<StatComponent>())
                {
                    mParent->getComponent<StatComponent>().restoreLife(mDamage);
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
*/
