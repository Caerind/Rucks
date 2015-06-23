#include "SpriteComponent.hpp"
#include "../World.hpp"

SpriteComponent::SpriteComponent(std::string const& id, sf::Vector2i sheetSize)
{
    mSheetSize = sheetSize;
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
    mTextureSize = static_cast<sf::Vector2i>(mSprite.getTexture()->getSize());
    mSprite.setOrigin(mSheetSize.x/2,mSheetSize.y/2);
}

void SpriteComponent::setTexture(std::string const& id)
{
    mSprite.setTexture(World::instance().getResources().getTexture(id));
    mTextureSize = static_cast<sf::Vector2i>(mSprite.getTexture()->getSize());
    mSprite.setOrigin(mSheetSize.x/2,mSheetSize.y/2);
}

void SpriteComponent::setTextureRect(sf::IntRect const& rect)
{
    mSprite.setTextureRect(rect);
    mSprite.setOrigin(mSheetSize.x/2,mSheetSize.y/2);
}

void SpriteComponent::setSheetSize(sf::Vector2i sheetSize)
{
    mSheetSize = sheetSize;
    mSprite.setOrigin(mSheetSize.x/2,mSheetSize.y/2);
}

sf::Vector2i SpriteComponent::getSheetSize() const
{
    return mSheetSize;
}

sf::Vector2i SpriteComponent::getTextureSize() const
{
    return mTextureSize;
}

sf::Vector2f SpriteComponent::getOrigin() const
{
    return mSprite.getOrigin();
}

void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
}


