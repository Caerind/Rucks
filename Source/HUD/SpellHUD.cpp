#include "SpellHUD.hpp"
#include "../World.hpp"

SpellHUD::SpellHUD()
{
    World::instance().getResources().loadTexture("spellshud","Assets/Textures/spellshud.png");
    sf::Texture& t = World::instance().getResources().getTexture("spellshud");
    for (std::size_t i = 0; i < mSprites.size(); i++)
    {
        mSprites[i].setTexture(t);
        mSprites[i].setTextureRect(sf::IntRect(0,0,64,64));
        mSprites[i].setPosition(i * 64, 0);
    }
    for (std::size_t i = 0; i < mShadows.size(); i++)
    {
        mShadows[i].setFillColor(sf::Color::Black); // TODO : Add Alpha component
        mShadows[i].setSize(sf::Vector2f(64,0));
        mShadows[i].setPosition(i * 64, 64);
    }
}

void SpellHUD::update(std::size_t id, Spell::Type type, sf::Time remaining, sf::Time cooldown)
{
    if (id >= 0 && id < 5)
    {
        mSprites[id].setTextureRect(sf::IntRect(type * 64,0,64,64));
        float d = remaining.asSeconds() / cooldown.asSeconds();
        mShadows[id].setSize(sf::Vector2f(64,- 64 * d));
    }
}

void SpellHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (std::size_t i = 0; i < mSprites.size(); i++)
    {
        target.draw(mSprites[i],states);
    }
    for (std::size_t i = 0; i < mShadows.size(); i++)
    {
        target.draw(mShadows[i],states);
    }
}
