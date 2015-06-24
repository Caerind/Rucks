#ifndef WEAPONCOMPONENT_HPP
#define WEAPONCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

class WeaponComponent : public es::Component
{
    public:
        WeaponComponent(float range, unsigned int damage, sf::Time cooldown);

        static std::string getId();

        void setRange(float range);
        float getRange() const;

        void setDamage(unsigned int damage);
        unsigned int getDamage() const;

        void setCooldown(sf::Time cooldown);
        sf::Time getCooldown() const;

        void attack();
        bool canAttack();

        void renderWeapon(sf::RenderTarget& target, sf::RenderStates states);

    private:
        float mRange;
        unsigned int mDamage;
        sf::Time mCooldown;
        sf::Clock mTimeSinceLastAttack;

        sf::Sprite mWeaponSprite;
};

#endif // WEAPONCOMPONENT_HPP
