#include "SpriteComponent.hpp"
#include "../World.hpp"

SpriteComponent::SpriteComponent(std::string const& id, sf::Vector2i sheetSize)
{
    mSheetSize = sheetSize;
    if (id != "")
    {
        setTexture(id);
    }
    setOrigin(mSheetSize.x/2,mSheetSize.y/2);
}

std::string SpriteComponent::getId()
{
    return "SpriteComponent";
}

void SpriteComponent::setTexture(std::string const& id)
{
    sf::Sprite::setTexture(World::instance().getResources().getTexture(id));
}

void SpriteComponent::setSheetSize(sf::Vector2i sheetSize)
{
    mSheetSize = sheetSize;
    setOrigin(mSheetSize.x/2,mSheetSize.y/2);
}

sf::Vector2i SpriteComponent::getSheetSize() const
{
    return mSheetSize;
}

sf::Vector2i SpriteComponent::getTextureSize() const
{
    return static_cast<sf::Vector2i>(getTexture()->getSize());
}


