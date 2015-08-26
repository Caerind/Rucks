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
    mManaCost = 10;
}

void Fireball::activate()
{
    assert(mDirection != sf::Vector2f() && mStricker != nullptr && mStricker->hasComponent<TransformComponent>());

    World::instance().getPrefab().createFireball(mStricker->getComponent<TransformComponent>().getPosition(), mStricker, mDirection);

    mCooldownTimer.restart();
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
