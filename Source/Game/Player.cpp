#include "Player.hpp"

Player::Player(World& world) : Entity(world)
{
}

unsigned int Player::getTypeId()
{
    return 2;
}

void Player::handleEvent(sf::Event const& event)
{
}

void Player::update(sf::Time dt)
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
}
