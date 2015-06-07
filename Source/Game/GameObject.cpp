#include "GameObject.hpp"
#include "World.hpp"

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
    mSprite.setTexture(mWorld.getApplication().getTexture("Assets/Textures/"+filename));
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
    renderLifeBar(target,states);
}

World& GameObject::getWorld()
{
    return mWorld;
}

bool GameObject::isValid()
{
    return mId != 0;
}

void GameObject::setLife(unsigned int life)
{
    mLife = life;
}

unsigned int GameObject::getLife() const
{
    return mLife;
}

void GameObject::setLifeMax(unsigned int lifeMax)
{
    mLifeMax = lifeMax;
}

unsigned int GameObject::getLifeMax() const
{
    return mLifeMax;
}

void GameObject::renderLifeBar(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mLife < mLifeMax)
    {
        sf::RectangleShape bg;
        bg.setSize(sf::Vector2f(32,7));
        bg.setPosition(-16 + getOrigin().x,-7-3);
        bg.setFillColor(sf::Color::Red);
        bg.setOutlineThickness(1);
        bg.setOutlineColor(sf::Color::Black);
        target.draw(bg,states);

        sf::RectangleShape l;
        l.setSize(sf::Vector2f(32.f * static_cast<float>(mLife) / static_cast<float>(mLifeMax),7));
        l.setPosition(-16 + getOrigin().x,-7-3);
        l.setFillColor(sf::Color::Green);
        target.draw(l,states);
    }
}
