#include "LifeComponent.hpp"

LifeComponent::LifeComponent(int life, int lifeMax)
{
    mLife = life;
    mLifeMax = lifeMax;
}

std::string LifeComponent::getId()
{
    return "LifeComponent";
}

void LifeComponent::setLife(int life)
{
    mLife = life;
}

void LifeComponent::setLifeMax(int lifeMax)
{
    mLifeMax = lifeMax;
}

int LifeComponent::getLife() const
{
    return mLife;
}

int LifeComponent::getLifeMax() const
{
    return mLifeMax;
}

void LifeComponent::setLifePercent(float percent)
{
    mLife = static_cast<int>(percent * static_cast<float>(mLifeMax) / 100.f);
}

float LifeComponent::getLifePercent() const
{
    if (mLifeMax == 0.f) // No Div By Zero
    {
        return 100.f;
    }
    return 100.f * static_cast<float>(mLife) / static_cast<float>(mLifeMax);
}

bool LifeComponent::isDead() const
{
    return mLife <= 0;
}

bool LifeComponent::isAlive() const
{
    return mLife > 0;
}

bool LifeComponent::inflige(int damage)
{
    bool res = damage >= mLife;
    mLife -= damage;
    mLife = std::max(0,mLife);
    mLife = std::min(mLife,mLifeMax);
    return res;
}

bool LifeComponent::restore(int heal)
{
    mLife += heal;
    mLife = std::max(0,mLife);
    mLife = std::min(mLife,mLifeMax);
    return mLife == mLifeMax;
}

void LifeComponent::fullRestore()
{
    mLife = mLifeMax;
}

void LifeComponent::setLifeBarSize(sf::Vector2f const& lifeBarSize)
{
    mLifeBarSize = lifeBarSize;
}

sf::Vector2f LifeComponent::getLifeBarSize() const
{
    return mLifeBarSize;
}

void LifeComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mLife < mLifeMax)
    {
        states.transform *= getTransform();

        sf::RectangleShape background;
        background.setPosition(-mLifeBarSize.x/2,0.f);
        background.setSize(mLifeBarSize);
        background.setFillColor(sf::Color::Red);
        background.setOutlineThickness(1.2f);
        background.setOutlineColor(sf::Color::Black);

        sf::RectangleShape life;
        life.setPosition(-mLifeBarSize.x/2,0.f);
        life.setSize(sf::Vector2f(mLifeBarSize.x * getLifePercent() * 0.01f, mLifeBarSize.y));
        life.setFillColor(sf::Color::Green);

        target.draw(background,states);
        target.draw(life,states);
    }
}
