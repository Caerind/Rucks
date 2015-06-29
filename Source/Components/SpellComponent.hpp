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

        void setSpell(std::size_t id);
        void setSpell(std::string const& name);
        Spell* getSpell();
        std::vector<Spell*> getSpells();

    private:
        std::size_t mActiveSpell;
        std::vector<Spell*> mSpells;
};

#endif // SPELLCOMPONENT_HPP
