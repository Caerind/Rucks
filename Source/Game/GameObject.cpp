#include "GameObject.hpp"

GameObject::GameObject(World& world) : mWorld(world), mId(0), mName("")
{
}

unsigned int GameObject::getTypeId()
{
    return 0;
}

void GameObject::setId(unsigned int id)
{
    mId = id;
}

unsigned int GameObject::getId() const
{
    return mId;
}

void GameObject::setName(std::string const& name)
{
    mName = name;
}

std::string GameObject::getName() const
{
    return mName;
}

void GameObject::setTexture(std::string const& filename)
{
    Sprite.setTexture(mWorld.getApplication().getTexture("Assets/Textures/"+filename));
}

void GameObject::setTextureRect(sf::IntRect rect)
{
    mSprite.setTextureRect(rect);
}

void GameObject::handleEvent(sf::Event const& event)
{
}

void GameObject::update(sf::Time dt)
{
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
}

World& GameObject::getWorld()
{
    return mWorld;
}

bool GameObject::isValid()
{
    return mId != 0;
}
