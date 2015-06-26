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

void SpriteComponent::setTexture(std::string const& id)
{
    sf::Sprite::setTexture(World::instance().getResources().getTexture(id));
}

sf::Vector2u SpriteComponent::getTextureSize() const
{
    if (getTexture() != nullptr)
    {
        return getTexture()->getSize();
    }
    return sf::Vector2u();
}


