#ifndef WEAPONCOMPONENT_HPP
#define WEAPONCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

class WeaponComponent : public es::Component, public sf::Transformable, public sf::Drawable
{
    public:
        enum Type
        {
            None,
            Sword,
            // TODO (#7#): More Weapons !
        };

        WeaponComponent(Type type = Type::None);
        WeaponComponent(float range, unsigned int damage, sf::Time cooldown);

        static std::string getId();

        void setType(Type type);
        Type getType() const;

        bool isLongRange() const;

        void setRange(float range);
        float getRange() const;

        void setDamage(unsigned int damage);
        unsigned int getDamage() const;

        void setCooldown(sf::Time cooldown);
        sf::Time getCooldown() const;

        void attack();
        bool canAttack();
        sf::Time getTimeSinceLastAttack() const;

        void setWeaponTransform(float x, float y, float rotation);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        static float getRange(Type type);
        static unsigned int getDamage(Type type);
        static sf::Time getCooldown(Type type);
        static std::string getTextureId(Type type);
        static sf::IntRect getTextureRect(Type type);

        static void loadWeaponTextures();
        static void releaseWeaponTextures();

    private:
        Type mType;

        float mRange;
        unsigned int mDamage;
        sf::Time mCooldown;

        sf::Clock mTimeSinceLastAttack;

        sf::Sprite mWeaponSprite;
};

#endif // WEAPONCOMPONENT_HPP
