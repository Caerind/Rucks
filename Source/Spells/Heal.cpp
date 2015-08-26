#include "Heal.hpp"
#include "../Components.hpp"

Heal::Heal()
{
    mType = Type::Heal;
    mName = "Heal";
    mRange = 500.f;
    mDamage = sf::Vector2i(20,30);
    mCooldown = sf::seconds(3.f);
    mCast = sf::seconds(0.3f);
    mManaCost = 10;
}

void Heal::activate()
{
    assert(mTarget != nullptr && mTarget->hasComponent<StatComponent>());

    mTarget->getComponent<StatComponent>().restoreLife(getDamage()); // TODO : Add Intelligence

    mCooldownTimer.restart();
}

bool Heal::canSpell()
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
    && thor::length(mTarget->getComponent<TransformComponent>().getPosition() - mStricker->getComponent<TransformComponent>().getPosition()) <= getRange()
    && mStricker->hasComponent<MonsterComponent>() == mTarget->hasComponent<MonsterComponent>())
    {
        return true;
    }
    return false;
}
