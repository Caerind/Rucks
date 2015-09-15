#include "Fireball.hpp"
#include "../World.hpp"

Fireball::Fireball()
{
    mType = Type::Fireball;
    mName = "Fireball";
    mRange = 500.f;
    mDamage = sf::Vector2i(30,40);
    mCooldown = sf::seconds(1.f);
    mCast = sf::seconds(0.1f);
    mManaCost = 30;
    mColor = sf::Color(155,0,0);
}

void Fireball::activate()
{
    assert(mDirection != sf::Vector2f() && mStricker != nullptr && mStricker->hasComponent<TransformComponent>());

    World::instance().createSpellBall(mStricker->getComponent<TransformComponent>().getPosition(), mDirection, this, mStricker->getId());

    mCooldownTimer.restart();

    if (mStricker->hasComponent<StatComponent>())
    {
        mStricker->getComponent<StatComponent>().useMana(mManaCost);
    }
}

bool Fireball::canSpell()
{
    assert(mStricker->hasComponent<StatComponent>());
    if (mStricker->getComponent<StatComponent>().getMana() >= getManaCost()
    && mCooldownTimer.getElapsedTime() >= getCooldown()
    && mDirection != sf::Vector2f())
    {
        return true;
    }
    return false;
}
