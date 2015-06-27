#ifndef WEAPONCOMPONENT_HPP
#define WEAPONCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include "../Game/Weapon.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

class WeaponComponent : public es::Component, public sf::Transformable, public sf::Drawable
{
    public:
        WeaponComponent();

        static std::string getId();

        void setWeapon(Weapon::Ptr weapon);
        Weapon::Ptr getWeapon() const;
        bool hasWeapon() const;
        void removeWeapon();
        Weapon::Ptr moveWeapon(); // get + remove

        bool isLongRange() const;

        void setRange(float range);
        float getRange() const;

        void setDamage(unsigned int damage);
        unsigned int getDamage() const;

        void setCooldown(sf::Time cooldown);
        sf::Time getCooldown() const;

        void attack(sf::Vector2f const& direction = sf::Vector2f());
        bool canAttack();
        sf::Time getTimeSinceLastAttack() const;

        void setWeaponTransform(float x, float y, float rotation);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        static void loadWeaponTextures();
        static void releaseWeaponTextures();

    private:
        Weapon::Ptr mWeapon;

        float mRange;
        unsigned int mDamage;
        sf::Time mCooldown;

        sf::Clock mTimeSinceLastAttack;

        sf::Sprite mWeaponSprite;
};

#endif // WEAPONCOMPONENT_HPP
