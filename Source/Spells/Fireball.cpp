#include "Fireball.hpp"
#include "../World.hpp"

Fireball::Fireball()
{
    mName = "Fireball";
    mRange = 500.f;
    mDamage = sf::Vector2i(30,40);
    mCooldown = sf::seconds(1.f);
    mCast = sf::seconds(0.1f);
    mManaCost = 10;
}

void Fireball::activate()
{
    if (mDirection != sf::Vector2f() && mStricker != nullptr)
    {
        if (mStricker->hasComponent<TransformComponent>())
        {
            World::instance().getPrefab().createFireball(mStricker->getComponent<TransformComponent>().getPosition(), mStricker, mDirection);
        }
    }
}
