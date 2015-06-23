#include "LifeComponent.hpp"

LifeComponent::LifeComponent(unsigned int life, unsigned int lifeMax)
{
    mLife = life;
    mLifeMax = lifeMax;
}

std::string LifeComponent::getId()
{
    return "LifeComponent";
}

void LifeComponent::setLife(unsigned int life)
{
    mLife = life;
}

void LifeComponent::setLifeMax(unsigned int lifeMax)
{
    mLifeMax = lifeMax;
}

unsigned int LifeComponent::getLife() const
{
    return mLife;
}

unsigned int LifeComponent::getLifeMax() const
{
    return mLifeMax;
}

bool LifeComponent::isDead() const
{
    return mLife <= 0;
}

bool LifeComponent::isAlive() const
{
    return mLife > 0;
}

bool LifeComponent::inflige(unsigned int damage)
{
    bool res = damage >= mLife;
    mLife -= damage;
    mLife = std::max((unsigned int)0,mLife);
    return res;
}

bool LifeComponent::restore(unsigned int heal)
{
    mLife += heal;
    mLife = std::max(mLife,mLifeMax);
    return mLife == mLifeMax;
}
