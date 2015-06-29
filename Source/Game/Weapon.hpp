#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "Item.hpp"

#include <SFML/System/Time.hpp>
#include <Thor/Math/Random.hpp>

#include "../Components/ProjectileComponent.hpp"

class Weapon : public Item
{
    public:
        typedef std::shared_ptr<Weapon> Ptr;

        enum Type
        {
            Sword,
            Bow,
        };

        Weapon();

        void setType(Type type);
        Type getType() const;

        bool isLongRange() const;

        void setRange(float range);
        float getRange() const;

        void setDamage(sf::Vector2i damageRange);
        void setDamage(int damageMin, int damageMax);
        void setDamageMin(int damageMin);
        void setDamageMax(int damageMax);
        int getDamageMin() const;
        int getDamageMax() const;
        sf::Vector2i getDamageRange() const;
        int getDamage() const;

        void setCooldown(sf::Time cooldown);
        sf::Time getCooldown() const;

        virtual bool isWeapon() const;

    protected:
        Type mType;

        float mRange;
        sf::Vector2i mDamage;
        sf::Time mCooldown;
};

#endif // WEAPON_HPP
