#include "SpellComponent.hpp"
#include "../World.hpp"

SpellComponent::SpellComponent()
{
    mCastingSpell = 0;
    mIsCasting = false;
    for (std::size_t i = 0; i < mSpells.size(); i++)
    {
        mSpells[i] = nullptr;
    }
    rd::Renderer::add(this);
}

SpellComponent::~SpellComponent()
{
    rd::Renderer::remove(this);
    for (std::size_t i = 0; i < mSpells.size(); i++)
    {
        delete mSpells[i];
    }
}

std::string SpellComponent::getId()
{
    return "SpellComponent";
}

Spell* SpellComponent::getSpell(std::size_t i)
{
    if (i >= 0 && i < mSpells.size())
    {
        return mSpells[i];
    }
    else
    {
        return nullptr;
    }
}

void SpellComponent::setSpell(std::size_t i, Spell* spell)
{
    if (i >= 0 && i < mSpells.size())
    {
        delete mSpells[i];
        mSpells[i] = spell;
    }
}

bool SpellComponent::isCasting() const
{
    return mIsCasting && mSpells[mCastingSpell] != nullptr;
}

sf::Time SpellComponent::getCasting() const
{
    return mCasting;
}

Spell* SpellComponent::getActiveSpell()
{
    if (mCastingSpell >= 0 && mCastingSpell < mSpells.size())
    {
        return mSpells[mCastingSpell];
    }
    return nullptr;
}

bool SpellComponent::canSpell(std::size_t i)
{
    if (i >= 0 && i < mSpells.size())
    {
        if (mSpells[i] != nullptr)
        {
            return mSpells[i]->canSpell() && !isCasting();
        }
    }
    return false;
}

void SpellComponent::spell(std::size_t i)
{
    if (i >= 0 && i < mSpells.size())
    {
        if (mSpells[i] != nullptr)
        {
            mCasting = sf::Time::Zero;
            mCastingSpell = i;
            mIsCasting = true;
            rd::Renderer::add(this);
        }
    }
}

void SpellComponent::update(sf::Time dt)
{
    if (mIsCasting && mSpells[mCastingSpell] != nullptr)
    {
        mCasting += dt;
        if (mCasting >= mSpells[mCastingSpell]->getCast())
        {
            mSpells[mCastingSpell]->activate();

            mIsCasting = false;
            mCasting = sf::Time::Zero;
            mCastingSpell = 0;
            rd::Renderer::remove(this);
        }
    }
}

void SpellComponent::render(sf::RenderTarget& target)
{
    if (isCasting())
    {
        sf::Vector2f pos = mPosition;
        if (hasParent())
        {
            if (mParent->hasComponent<TransformComponent>())
            {
                pos += mParent->getComponent<TransformComponent>().getPosition();
            }
        }
        rd::Sprite::setTexture(World::instance().getResources().getTexture("spell"));
        rd::Sprite::setTextureRect(sf::IntRect(0,0,8,8)); // TODO : Animated spell
        rd::Sprite::setOrigin(4.f,4.f);
        rd::Sprite::setColor(mSpells[mCastingSpell]->getColor());
        rd::Sprite::setPosition(pos);
        rd::Sprite::render(target);
    }
}

void SpellComponent::setSpellPosition(float x, float y)
{
    mPosition = sf::Vector2f(x,y);
}
