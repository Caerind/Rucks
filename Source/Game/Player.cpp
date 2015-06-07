#include "Player.hpp"
#include "World.hpp"
#include "OnlineManager.hpp"

Player::Player(World& world) : Entity(world)
{
    mTextName.setCharacterSize(10);
    mTextName.setFont(mWorld.getApplication().getFont("Assets/Fonts/aniron.ttf"));
}

unsigned int Player::getTypeId()
{
    return 2;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
    if (mWorld.getObjectManager().getPlayer() != nullptr)
        if (mWorld.getObjectManager().getPlayer()->getId() != mId)
            target.draw(mTextName,states);
    renderLifeBar(target,states);
}

void Player::setName(std::string const& name)
{
    mName = name;
    mTextName.setString(name);
    mTextName.setPosition(-mTextName.getGlobalBounds().width/2 + getOrigin().x,-20);
}
