#ifndef SPELLCOMPONENT_HPP
#define SPELLCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class SpellComponent : public es::Component
{
    public:
        enum Type
        {
            None,
            Fireball,
            Heal,
        };

        SpellComponent();

        static std::string getId();

        void setType(Type type);
        Type getType() const;

        void setRange(float range);
        float getRange() const;

        void setDamage(int damage);
        int getDamage() const;

        void setCooldown(sf::Time cooldown);
        sf::Time getCooldown() const;

        void spell(sf::Vector2f const& direction = sf::Vector2f());
        bool canSpell();
        sf::Time getTimeSinceLastSpell() const;

    private:
        Type mType;

        float mRange;
        int mDamage;
        sf::Time mCooldown;

        sf::Clock mTimeSinceLastSpell;
};

#endif // SPELLCOMPONENT_HPP
