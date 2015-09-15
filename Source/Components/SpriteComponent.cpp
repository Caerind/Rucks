#include "SpriteComponent.hpp"
#include "../World.hpp"

SpriteComponent::SpriteComponent(std::string const& id)
{
    mZ = 16.f;
    rd::Renderer::add(this);
    if (id != "")
    {
        setTexture(id);
    }
}

SpriteComponent::~SpriteComponent()
{
    rd::Renderer::remove(this);
}

std::string SpriteComponent::getId()
{
    return "SpriteComponent";
}

void SpriteComponent::setTexture(std::string const& id)
{
    rd::Sprite::setTexture(World::instance().getResources().getTexture(id));
}

sf::Vector2u SpriteComponent::getTextureSize() const
{
    if (getTexture() != nullptr)
    {
        return getTexture()->getSize();
    }
    return sf::Vector2u();
}

void SpriteComponent::render(sf::RenderTarget& target)
{
    if (hasParent())
    {
        if (mParent->hasComponent<TransformComponent>())
        {
            rd::Sprite::setPosition(mParent->getComponent<TransformComponent>().getPosition());
            rd::Sprite::setRotation(mParent->getComponent<TransformComponent>().getRotation());
        }
    }
    target.draw(*this);
}

sf::FloatRect SpriteComponent::getBounds()
{
    if (hasParent())
    {
        if (mParent->hasComponent<TransformComponent>())
        {
            rd::Sprite::setPosition(mParent->getComponent<TransformComponent>().getPosition());
        }
    }
    return rd::Sprite::getBounds();
}


