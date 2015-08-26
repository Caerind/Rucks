#include "SpellComponent.hpp"
#include "../../Lib/EntitySystem/Entity.hpp"
#include "../Components.hpp"
#include "../World.hpp"

SpellComponent::SpellComponent()
{
    mWasRunning = false;
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

bool SpellComponent::canSpell()
{
    return mCaster.isExpired();
}

void SpellComponent::spell()
{
    Spell* spell = getSpell(mActiveSpell);
    if (canSpell() &&  spell != nullptr)
    {
        if (spell->canSpell())
        {
            if (hasParent())
            {
                if (mParent->hasComponent<StatComponent>())
                {
                    mParent->getComponent<StatComponent>().useMana(spell->getManaCost());
                }
            }
            // TODO : Fix CallbackTimer
            //mCaster.connect0(std::bind(&Spell::activate, spell));
            mWasRunning = true;
            mCaster.restart(spell->getCast());
        }
    }
}

void SpellComponent::update(es::Entity::Ptr stricker, es::Entity::Ptr target, sf::Vector2f const& position, sf::Vector2f const& direction)
{
    if (mWasRunning && mCaster.isExpired())
    {
        Spell* spell = getActiveSpell();
        if (spell != nullptr)
        {
            spell->setStricker(stricker);
            spell->setTarget(target);
            spell->setPosition(position);
            spell->setDirection(direction);

            spell->activate();
        }
        mWasRunning = false;
    }
}

sf::Time SpellComponent::getRemainingCastTime()
{
    return mCaster.getRemainingTime();
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
