#include "Entity.hpp"

Entity::Entity(World& world) : GameObject(world)
{
}

unsigned int Entity::getTypeId()
{
    return 1;
}
