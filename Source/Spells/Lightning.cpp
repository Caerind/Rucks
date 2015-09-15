#include "Lightning.hpp"
#include "../Components.hpp"

Lightning::Lightning()
{
    mType = Type::Lightning;
    mName = "Lightning";
    mRange = 500.f;
    mDamage = sf::Vector2i(20,30);
    mCooldown = sf::seconds(2.f);
    mCast = sf::seconds(0.8f);
    mManaCost = 30;
    mColor = sf::Color(250,170,70);
}

void Lightning::activate()
{
    assert(mTarget != nullptr && mTarget->hasComponent<StatComponent>());

    if (mTarget->getComponent<StatComponent>().inflige(getDamage())) // TODO : Add Intelligence
    {
        if (mStricker != nullptr)
        {
            if (mStricker->hasComponent<StatComponent>())
            {
                mStricker->getComponent<StatComponent>().addExperience(10); // TODO : Add Experience
            }
        }
    }

    mCooldownTimer.restart();

    if (mStricker != nullptr)
    {
        if (mStricker->hasComponent<StatComponent>())
        {
            mStricker->getComponent<StatComponent>().useMana(mManaCost);
        }
    }
}

bool Lightning::canSpell()
{
    if (mTarget == nullptr)
    {
        return false;
    }
    assert(mStricker->hasComponent<TransformComponent>());
    assert(mStricker->hasComponent<StatComponent>());
    assert(mTarget->hasComponent<TransformComponent>());
    if (mStricker->getComponent<StatComponent>().getMana() >= getManaCost()
    && mCooldownTimer.getElapsedTime() >= getCooldown()
    && thor::length(mTarget->getComponent<TransformComponent>().getPosition() - mStricker->getComponent<TransformComponent>().getPosition()) <= getRange())
    {
        return true;
    }
    return false;
}
