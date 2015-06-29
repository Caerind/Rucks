#include "StatComponent.hpp"

////////////////////////////////////////////////////////////
StatComponent::StatComponent()
{
    mLife = 100;
    mLifeMax = 100;
    mMana = 100;
    mManaMax = 100;
    mLevel = 1;
    mExperience = 0;
    mStrength = 1;
    mIntelligence = 1;
    mAgility = 1;
}

////////////////////////////////////////////////////////////
std::string StatComponent::getId()
{
    return "StatComponent";
}

////////////////////////////////////////////////////////////
void StatComponent::setLife(int life)
{
    mLife = life;
}

////////////////////////////////////////////////////////////
int StatComponent::getLife() const
{
    return mLife;
}

////////////////////////////////////////////////////////////
void StatComponent::setLifeMax(int lifeMax)
{
    mLifeMax = lifeMax;
}

////////////////////////////////////////////////////////////
int StatComponent::getLifeMax() const
{
    return mLifeMax;
}

////////////////////////////////////////////////////////////
bool StatComponent::isDead() const
{
    return mLife <= 0;
}

////////////////////////////////////////////////////////////
bool StatComponent::isAlive() const
{
    return mLife > 0;
}

////////////////////////////////////////////////////////////
bool StatComponent::inflige(int damage)
{
    bool res = damage >= mLife;
    mLife -= damage;
    mLife = std::max(0,mLife);
    mLife = std::min(mLife,mLifeMax);
    return res;
}

////////////////////////////////////////////////////////////
bool StatComponent::restoreLife(int heal)
{
    mLife += heal;
    mLife = std::max(0,mLife);
    mLife = std::min(mLife,mLifeMax);
    return mLife == mLifeMax;
}

////////////////////////////////////////////////////////////
void StatComponent::fullRestoreLife()
{
    mLife = mLifeMax;
}

////////////////////////////////////////////////////////////
void StatComponent::setLifeBarSize(sf::Vector2f const& size)
{
    mLifeBarSize = size;
}

////////////////////////////////////////////////////////////
sf::Vector2f StatComponent::getLifeBarSize() const
{
    return mLifeBarSize;
}

////////////////////////////////////////////////////////////
void StatComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
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
        life.setSize(sf::Vector2f(mLifeBarSize.x * static_cast<float>(mLife) / static_cast<float>(mLifeMax), mLifeBarSize.y));
        life.setFillColor(sf::Color::Green);

        target.draw(background,states);
        target.draw(life,states);
    }
}

////////////////////////////////////////////////////////////
void StatComponent::setMana(int mana)
{
    mMana = mana;
}

////////////////////////////////////////////////////////////
int StatComponent::getMana() const
{
    return mMana;
}

////////////////////////////////////////////////////////////
void StatComponent::setManaMax(int manaMax)
{
    mManaMax = manaMax;
}

////////////////////////////////////////////////////////////
int StatComponent::getManaMax() const
{
    return mManaMax;
}

////////////////////////////////////////////////////////////
void StatComponent::useMana(int use)
{
    mMana -= use;
    mMana = std::max(0,mMana);
    mMana = std::min(mMana,mManaMax);
}

////////////////////////////////////////////////////////////
void StatComponent::restoreMana(int restore)
{
    mMana += restore;
    mMana = std::max(0,mMana);
    mMana = std::min(mMana,mManaMax);
}

////////////////////////////////////////////////////////////
void StatComponent::fullRestoreMana()
{
    mMana = mManaMax;
}

////////////////////////////////////////////////////////////
void StatComponent::setLevel(int level)
{
    mLevel = level;
}

////////////////////////////////////////////////////////////
int StatComponent::getLevel() const
{
    return mLevel;
}

////////////////////////////////////////////////////////////
void StatComponent::setExperience(int experience)
{
    mExperience = experience;
}

////////////////////////////////////////////////////////////
int StatComponent::getExperience() const
{
    return mExperience;
}

////////////////////////////////////////////////////////////
bool StatComponent::addExperience(int experience)
{
    if (experience >= getExperienceRemaning())
    {
        int diff = experience - getExperienceRemaning();
        addLevel();
        mExperience = diff;
    }
    else
    {
        mExperience += experience;
        mExperience = std::max(0,mExperience);
        return false;
    }
}

////////////////////////////////////////////////////////////
void StatComponent::addLevel()
{
    mLevel++;
    mExperience = 0;
}

////////////////////////////////////////////////////////////
int StatComponent::getExperienceRemaning() const
{
    return 100 - mExperience; // TODO : Better Formule For Experience
}

////////////////////////////////////////////////////////////
void StatComponent::setStrength(int strength)
{
    mStrength = strength;
}

////////////////////////////////////////////////////////////
int StatComponent::getStrength() const
{
    return mStrength;
}

////////////////////////////////////////////////////////////
void StatComponent::setIntelligence(int intelligence)
{
    mIntelligence = intelligence;
}

////////////////////////////////////////////////////////////
int StatComponent::getIntelligence() const
{
    return mIntelligence;
}

////////////////////////////////////////////////////////////
void StatComponent::setAgility(int agility)
{
    mAgility = agility;
}

////////////////////////////////////////////////////////////
int StatComponent::getAgility() const
{
    return mAgility;
}

