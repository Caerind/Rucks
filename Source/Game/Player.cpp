#include "Player.hpp"
#include "World.hpp"
#include "OnlineManager.hpp"

Player::Player(World& world) : Entity(world)
{
}

unsigned int Player::getTypeId()
{
    return 2;
}

void Player::handleEvent(sf::Event const& event)
{
    if (event.type == sf::Event::MouseButtonPressed
    && event.mouseButton.button == sf::Mouse::Left
    && mSprite.getGlobalBounds().contains(mWorld.getApplication().getMousePositionView(mWorld.getView()))
    && mWorld.getObjectManager().getPlayer() != nullptr)
    {
        float dx = mWorld.getObjectManager().getPlayer()->getPosition().x - getPosition().x;
        float dy = mWorld.getObjectManager().getPlayer()->getPosition().y - getPosition().y;
        float d = std::sqrt(dx * dx + dy * dy);
        if (d < mWorld.getObjectManager().getPlayer()->getRange())
        {
            mWorld.getOnlineManager().sendAttack(mId);
        }
    }
}

void Player::update(sf::Time dt)
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
    /*
    if (!mainPlayer)
    {
        renderName(target,states);
    }
    */
    renderLifeBar(target,states);
}

void Player::setRange(float range)
{
    mRange = range;
}

float Player::getRange() const
{
    return mRange;
}
