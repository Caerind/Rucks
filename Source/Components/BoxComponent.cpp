#include "BoxComponent.hpp"
#include "../../Aharos/EntitySystem/Entity.hpp"
#include "TransformComponent.hpp"

BoxComponent::BoxComponent()
{
    rd::Renderer::add(this);
    mZ = 2000.f;
}

BoxComponent::~BoxComponent()
{
    rd::Renderer::remove(this);
}

std::string BoxComponent::getId()
{
    return "BoxComponent";
}

void BoxComponent::setSize(float sizeX, float sizeY)
{
    mSize.x = sizeX;
    mSize.y = sizeY;
}

void BoxComponent::setSize(sf::Vector2f const& size)
{
    mSize = size;
}

sf::Vector2f BoxComponent::getSize() const
{
    return mSize;
}

sf::FloatRect BoxComponent::getBounds()
{
    return sf::FloatRect(getPosition(),getSize());
}

bool BoxComponent::intersects(sf::FloatRect const& rect)
{
    return getBounds().intersects(rect);
}

bool BoxComponent::contains(sf::Vector2f const& pos)
{
    return getBounds().contains(pos);
}

void BoxComponent::render(sf::RenderTarget& target)
{
    sf::RectangleShape shape;
    shape.setSize(getSize());
    shape.setPosition(getPosition());
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1.5f);
    shape.setOutlineColor(sf::Color::Green);
    target.draw(shape);
}

void BoxComponent::setPosition(sf::Vector2f const& position)
{
    sf::Transformable::setPosition(position);
}

sf::Vector2f BoxComponent::getPosition() const
{
    sf::Vector2f position = sf::Transformable::getPosition()-getOrigin();
    if (hasParent())
    {
        if (mParent->hasComponent<TransformComponent>())
        {
            position += mParent->getComponent<TransformComponent>().getPosition();
        }
    }
    return position;
}
