#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "Item.hpp"

#include <SFML/System/Time.hpp>

#include "../Components/ProjectileComponent.hpp"

class Weapon : public Item
{
    public:
        typedef std::shared_ptr<Weapon> Ptr;

        enum Type
        {
            None,
            Sword,
            Bow,
        };

        Weapon();

        void setType(Type type);
        Type getType() const;

        bool isLongRange() const;
        ProjectileComponent::Type getProjectileType() const;

        void setRange(float range);
        float getRange() const;

        void setDamage(int damage);
        int getDamage() const;

        void setCooldown(sf::Time cooldown);
        sf::Time getCooldown() const;

        virtual bool isWeapon() const;

    protected:
        Type mType;

        float mRange;
        int mDamage;
        sf::Time mCooldown;
};

#endif // WEAPON_HPP
