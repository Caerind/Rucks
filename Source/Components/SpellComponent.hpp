#ifndef SPELLCOMPONENT_HPP
#define SPELLCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

#include "../Spells.hpp"

#include <vector>

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

    private:
        std::size_t mActiveSpell;
        std::vector<Spell*> mSpells;
};

#endif // SPELLCOMPONENT_HPP
