#include "StatComponent.hpp"
#include "../../Aharos/EntitySystem/Entity.hpp"
#include "../Components.hpp"

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

    mZ = 2200.f;

    rd::Renderer::add(this);
}

////////////////////////////////////////////////////////////
StatComponent::~StatComponent()
{
    rd::Renderer::remove(this);
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
sf::FloatRect StatComponent::getBounds()
{
    return sf::FloatRect(sf::Vector2f(getPosition() + sf::Vector2f(-mLifeBarSize.x/2,0.f)),mLifeBarSize);
}

////////////////////////////////////////////////////////////
void StatComponent::render(sf::RenderTarget& target)
{
    if (mLife < mLifeMax || mMana < mManaMax)
    {
        sf::Vector2f pos = getPosition() + sf::Vector2f(-mLifeBarSize.x/2,0.f);

        sf::RectangleShape background;
        background.setPosition(pos);
        background.setSize(mLifeBarSize);
        background.setFillColor(sf::Color::Red);
        background.setOutlineThickness(1.2f);
        background.setOutlineColor(sf::Color::Black);

        sf::RectangleShape life;
        life.setPosition(pos);
        life.setSize(sf::Vector2f(mLifeBarSize.x * static_cast<float>(mLife) / static_cast<float>(mLifeMax), mLifeBarSize.y));
        life.setFillColor(sf::Color::Green);

        sf::RectangleShape bg;
        bg.setPosition(pos.x,pos.y + mLifeBarSize.y);
        bg.setSize(sf::Vector2f(mLifeBarSize.x,(2.f/5.f) * mLifeBarSize.y));
        bg.setFillColor(sf::Color(25,25,100));
        bg.setOutlineThickness(1.2f);
        bg.setOutlineColor(sf::Color::Black);

        sf::RectangleShape mana;
        mana.setPosition(pos.x,pos.y + mLifeBarSize.y);
        mana.setSize(sf::Vector2f(mLifeBarSize.x * static_cast<float>(mMana) / static_cast<float>(mManaMax), (2.f/5.f) * mLifeBarSize.y));
        mana.setFillColor(sf::Color::Blue);

        target.draw(background);
        target.draw(life);
        target.draw(bg);
        target.draw(mana);
    }
}

////////////////////////////////////////////////////////////
void StatComponent::setPosition(sf::Vector2f const& position)
{
    mLifeBarPosition = position;
}

////////////////////////////////////////////////////////////
sf::Vector2f StatComponent::getPosition() const
{
    sf::Vector2f position = mLifeBarPosition;
    if (hasParent())
    {
        if (mParent->hasComponent<TransformComponent>())
        {
            position += mParent->getComponent<TransformComponent>().getPosition();
        }
    }
    return position;
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
        return true;
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

////////////////////////////////////////////////////////////
void StatComponent::setMoney(int money)
{
    mMoney = money;
}

////////////////////////////////////////////////////////////
int StatComponent::getMoney() const
{
    return mMoney;
}

////////////////////////////////////////////////////////////
void StatComponent::spendMoney(int money)
{
    mMoney -= money;
}

////////////////////////////////////////////////////////////
void StatComponent::earnMoney(int money)
{
    mMoney += money;
}
