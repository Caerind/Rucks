#ifndef SPELLHUD_HPP
#define SPELLHUD_HPP

#include <array>
#include <SFML/Graphics.hpp>
#include "../Spells/Spell.hpp"

class SpellHUD : public sf::Transformable, public sf::Drawable
{
    public:
        SpellHUD();

        void update(std::size_t id, Spell::Type type, sf::Time remaining, sf::Time cooldown);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        std::array<sf::Sprite,5> mSprites;
        std::array<sf::RectangleShape,5> mShadows;
};

#endif // SPELLHUD_HPP
