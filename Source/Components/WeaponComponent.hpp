#ifndef WEAPONCOMPONENT_HPP
#define WEAPONCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"
#include "../../Lib/EntitySystem/Entity.hpp"

#include "../Game/Weapon.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Thor/Math/Random.hpp>

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

        void attack();
        void attack(es::Entity::Ptr target);
        void attack(sf::Vector2f const& direction);
        bool canAttack();
        sf::Time getTimeSinceLastAttack() const;

        void setWeaponTransform(float x, float y, float rotation);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        static void loadWeaponTextures();
        static void releaseWeaponTextures();

    private:
        Weapon::Ptr mWeapon;

        float mRange;
        sf::Vector2i mDamage;
        sf::Time mCooldown;

        sf::Clock mTimeSinceLastAttack;

        sf::Sprite mWeaponSprite;
};

#endif // WEAPONCOMPONENT_HPP
