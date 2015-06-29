#include "Flash.hpp"
#include "../Components.hpp"

Flash::Flash()
{
    mName = "Flash";
    mRange = 500.f;
    mDamage = sf::Vector2i(0,0);
    mCooldown = sf::seconds(20.f);
    mCast = sf::seconds(0.3f);
    mManaCost = 30;
}

void Flash::activate()
{
    if (mStricker != nullptr)
    {
        if (mStricker->hasComponent<TransformComponent>())
        {
            mStricker->getComponent<TransformComponent>().setPosition(mPosition);
        }
    }
}
