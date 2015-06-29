#ifndef STATCOMPONENT_HPP
#define STATCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class StatComponent : public es::Component, public sf::Drawable, public sf::Transformable
{
    public:
        StatComponent();

        static std::string getId();


        //
        // Life
        //
        void setLife(int life);
        int getLife() const;

        void setLifeMax(int lifeMax);
        int getLifeMax() const;

        bool isDead() const;
        bool isAlive() const;

        bool inflige(int damage); // return true if is has been killed by the damage
        bool restoreLife(int heal); // return true if full life
        void fullRestoreLife();

        void setLifeBarSize(sf::Vector2f const& size);
        sf::Vector2f getLifeBarSize() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        //
        // Mana
        //
        void setMana(int mana);
        int getMana() const;

        void setManaMax(int manaMax);
        int getManaMax() const;

        void useMana(int use);
        void restoreMana(int restore);
        void fullRestoreMana();

        //
        // Level & Experience
        //
        void setLevel(int level);
        int getLevel() const;

        void setExperience(int experience);
        int getExperience() const;

        bool addExperience(int experience); // return true if level up
        void addLevel();
        int getExperienceRemaning() const;

        //
        // Fighting Stats
        //
        void setStrength(int strength);
        int getStrength() const;

        void setIntelligence(int intelligence);
        int getIntelligence() const;

        void setAgility(int agility);
        int getAgility() const;

    private:
        int mLife;
        int mLifeMax;
        sf::Vector2f mLifeBarSize;

        int mMana;
        int mManaMax;

        int mLevel;
        int mExperience;

        int mStrength;
        int mIntelligence;
        int mAgility;
};

#endif // STATCOMPONENT_HPP
