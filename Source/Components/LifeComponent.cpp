#include "LifeComponent.hpp"

LifeComponent::LifeComponent(unsigned int life, unsigned int lifeMax)
{
    mLife = life;
    mLifeMax = lifeMax;
}

std::string LifeComponent::getId()
{
    return "LifeComponent";
}

void LifeComponent::setLife(unsigned int life)
{
    mLife = life;
}

void LifeComponent::setLifeMax(unsigned int lifeMax)
{
    mLifeMax = lifeMax;
}

unsigned int LifeComponent::getLife() const
{
    return mLife;
}

unsigned int LifeComponent::getLifeMax() const
{
    return mLifeMax;
}

bool LifeComponent::isDead() const
{
    return mLife <= 0;
}

bool LifeComponent::isAlive() const
{
    return mLife > 0;
}

bool LifeComponent::inflige(unsigned int damage)
{
    bool res = damage >= mLife;
    mLife -= damage;
    mLife = std::max((unsigned int)0,mLife);
    return res;
}

bool LifeComponent::restore(unsigned int heal)
{
    mLife += heal;
    mLife = std::max(mLife,mLifeMax);
    return mLife == mLifeMax;
}

void LifeComponent::renderLifeBar(sf::RenderTarget& target, sf::RenderStates states)
{
    if (mLife < mLifeMax)
    {
        sf::RectangleShape bg;
        bg.setPosition(-15.f,-20.f);
        bg.setSize(sf::Vector2f(30,6));
        bg.setFillColor(sf::Color::Red);
        bg.setOutlineThickness(1.2f);
        bg.setOutlineColor(sf::Color::Black);

        sf::RectangleShape l;
        l.setPosition(-15.f,-20.f);
        l.setSize(sf::Vector2f(30.f * static_cast<float>(mLife) / static_cast<float>(mLifeMax),6));
        l.setFillColor(sf::Color::Green);

        target.draw(bg,states);
        target.draw(l,states);
    }
}
