#ifndef WEAPONCOMPONENT_HPP
#define WEAPONCOMPONENT_HPP

#include "../../Aharos/EntitySystem/Component.hpp"
#include "../../Aharos/EntitySystem/Entity.hpp"

#include "../../Aharos/Renderer/Renderer.hpp"
#include "../../Aharos/Renderer/Sprite.hpp"

#include "../Game/Weapon.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Thor/Math/Random.hpp>

class WeaponComponent : public es::Component, public rd::Sprite
{
    public:
        WeaponComponent();
        ~WeaponComponent();

        static std::string getId();

        void render(sf::RenderTarget& target);

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

        static void loadWeaponTextures();
        static void releaseWeaponTextures();

    private:
        Weapon::Ptr mWeapon;

        sf::Vector2f mPosition;

        float mRange;
        sf::Vector2i mDamage;
        sf::Time mCooldown;

        sf::Clock mTimeSinceLastAttack;
};

#endif // WEAPONCOMPONENT_HPP
