#include "Entity.hpp"

Entity::Entity(World& world) : GameObject(world)
{
}

unsigned int Entity::getTypeId()
{
    return 1;
}

void Entity::setLife(unsigned int life)
{
    mLife = life;
}

unsigned int Entity::getLife() const
{
    return mLife;
}

void Entity::setLifeMax(unsigned int lifeMax)
{
    mLifeMax = lifeMax;
}

unsigned int Entity::getLifeMax() const
{
    return mLifeMax;
}
