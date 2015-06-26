#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "Item.hpp"

#include <SFML/System/Time.hpp>

class Weapon : public Item
{
    public:
        Weapon();

        void setRange(float range);
        float getRange() const;

        void setDamage(int damage);
        int getDamage() const;

        void setCooldown(sf::Time cooldown);
        sf::Time getCooldown() const;

    protected:
        float mRange;
        int mDamage;
        sf::Time mCooldown;
};

#endif // WEAPON_HPP
