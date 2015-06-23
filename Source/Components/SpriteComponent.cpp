#include "SpriteComponent.hpp"
#include "../World.hpp"

SpriteComponent::SpriteComponent(std::string const& id)
{
    if (id != "")
    {
        setTexture(id);
    }
}

std::string SpriteComponent::getId()
{
    return "SpriteComponent";
}

void SpriteComponent::setTexture(sf::Texture& texture)
{
    mSprite.setTexture(texture);
    mSprite.setOrigin(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2);
}

void SpriteComponent::setTexture(std::string const& id)
{
    mSprite.setTexture(World::instance().getResources().getTexture(id));
    mSprite.setOrigin(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2);
}

void SpriteComponent::setTextureRect(sf::IntRect const& rect)
{
    mSprite.setTextureRect(rect);
    mSprite.setOrigin(mSprite.getGlobalBounds().width/2,mSprite.getGlobalBounds().height/2);
}

void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}


