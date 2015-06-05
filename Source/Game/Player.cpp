#include "Player.hpp"

Player::Player(World& world) : Entity(world)
{
}

unsigned int Player::getTypeId()
{
    return 2;
}
