#ifndef SPELLCOMPONENT_HPP
#define SPELLCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include "../../Lib/Aharos/Application.hpp"

#include "../Spells.hpp"

#include <vector>

#include <Thor/Time/CallbackTimer.hpp>

class SpellComponent : public es::Component
{
    public:
        SpellComponent();
        ~SpellComponent();

        static std::string getId();

        void learnSpell(Spell* spell);

        std::size_t getSpellCount() const;

        void setActiveSpell(std::size_t id);
        std::size_t getActiveSpellId() const;
        Spell* getActiveSpell();

        Spell* getSpell(std::size_t id);

        bool canSpell();
        void spell();
        void update(es::Entity::Ptr stricker, es::Entity::Ptr target, sf::Vector2f const& position, sf::Vector2f const& direction);
        sf::Time getRemainingCastTime();

    private:
        std::size_t mActiveSpell;
        std::vector<Spell*> mSpells;

        thor::CallbackTimer mCaster;
        bool mWasRunning; // Fix until we've got a problem with callback
};

#endif // SPELLCOMPONENT_HPP
