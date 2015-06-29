#include "Heal.hpp"
#include "../Components.hpp"

Heal::Heal()
{
    mName = "Heal";
    mRange = 500.f;
    mDamage = sf::Vector2i(20,30);
    mCooldown = sf::seconds(3.f);
    mCast = sf::seconds(0.2f);
    mManaCost = 10;
}

void Heal::activate()
{
    if (mTarget != nullptr)
    {
        if (mTarget->hasComponent<StatComponent>())
        {
            mTarget->getComponent<StatComponent>().restoreLife(getDamage()); // TODO : Add Intelligence
        }
    }
}
