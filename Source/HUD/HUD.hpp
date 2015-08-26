#ifndef HUD_HPP
#define HUD_HPP

#include "SpellHUD.hpp"

class HUD : public sf::Drawable
{
    public:
        HUD();

        SpellHUD& getSpells();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        SpellHUD mSpellHUD;
};

#endif // HUD_HPP
