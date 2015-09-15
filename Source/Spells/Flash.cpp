#include "Flash.hpp"
#include "../Components.hpp"

Flash::Flash()
{
    mType = Type::Flash;
    mName = "Flash";
    mRange = 1000.f;
    mDamage = sf::Vector2i(0,0);
    mCooldown = sf::seconds(20.f);
    mCast = sf::seconds(0.3f);
    mManaCost = 100;
    mColor = sf::Color(250,250,50);
}

void Flash::activate()
{
    assert(mStricker != nullptr && mStricker->hasComponent<TransformComponent>());

    mStricker->getComponent<TransformComponent>().setPosition(mPosition);

    mCooldownTimer.restart();

    if (mStricker != nullptr)
    {
        if (mStricker->hasComponent<StatComponent>())
        {
            mStricker->getComponent<StatComponent>().useMana(mManaCost);
        }
    }
}

bool Flash::canSpell()
{
    assert(mStricker->hasComponent<TransformComponent>());
    assert(mStricker->hasComponent<StatComponent>());
    if (mStricker->getComponent<StatComponent>().getMana() >= getManaCost()
    && mCooldownTimer.getElapsedTime() >= getCooldown()
    && thor::length(mPosition - mStricker->getComponent<TransformComponent>().getPosition()) <= getRange())
    {
        return true;
    }
    return false;
}
