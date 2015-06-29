#ifndef SPELL_HPP
#define SPELL_HPP

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <Thor/Math/Random.hpp>

#include "../../Lib/EntitySystem/Entity.hpp"

class Spell
{
    public:
        Spell();
        virtual ~Spell();

        virtual void activate() = 0;

        void setStricker(es::Entity::Ptr stricker);
        void setTarget(es::Entity::Ptr target);
        void setDirection(sf::Vector2f const& direction);
        void setPosition(sf::Vector2f const& position);

        std::string getName() const;
        float getRange() const;
        int getDamageMin() const;
        int getDamageMax() const;
        sf::Vector2i getDamageRange() const;
        int getDamage() const;
        sf::Time getCooldown() const;
        sf::Time getCast() const;
        int getManaCost() const;

    protected:
        std::string mName;
        float mRange;
        sf::Vector2i mDamage;
        sf::Time mCooldown;
        sf::Time mCast;
        int mManaCost;

        es::Entity::Ptr mStricker;
        es::Entity::Ptr mTarget;
        sf::Vector2f mDirection;
        sf::Vector2f mPosition;
};

#endif // SPELL_HPP
