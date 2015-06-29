#include "Lightning.hpp"
#include "../Components.hpp"

Lightning::Lightning()
{
    mName = "Lightning";
    mRange = 500.f;
    mDamage = sf::Vector2i(20,30);
    mCooldown = sf::seconds(2.f);
    mCast = sf::seconds(0.3f);
    mManaCost = 10;
}

void Lightning::activate()
{
    if (mTarget != nullptr)
    {
        if (mTarget->hasComponent<StatComponent>())
        {
            mTarget->getComponent<StatComponent>().inflige(getDamage()); // TODO : Add Intelligence
            // TODO : If get killed, add exp to the stricker
        }
    }
}
