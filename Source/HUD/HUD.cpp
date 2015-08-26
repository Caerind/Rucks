#include "HUD.hpp"

HUD::HUD()
{
    mSpellHUD.setPosition(800-320,600-64);
}

SpellHUD& HUD::getSpells()
{
    return mSpellHUD;
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSpellHUD,states);
}
